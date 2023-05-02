#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include <shared_mutex>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <tuple>
#include <thread>
#include <atomic>

#include "../Data/Block.hpp"
#include "../Listeners/FilePrinter.hpp"
#include "../Listeners/Printer.hpp"



//Описание для обработчика процесса
template <class P>
struct ProcessD
{
    std::condition_variable cv;
    std::mutex mutex;
    std::queue<std::shared_ptr<Data::Block>> queue;
    P worker;
};

//Обработчик блоков команд
struct CommandProcessor
{

        static CommandProcessor& getInstance()
        {
            static CommandProcessor instance;
            return instance;
        }
//Обработчик нового блока
        void push(std::shared_ptr<Data::Block> block)
        {
            pushBlock(logger,       block);
            pushBlock(fileWorker,   block);
        }

//То что крутится в потоке
        template<class Worker>
        void task(ProcessD<Worker>& wr)
        {
            while(true)
            {
                std::unique_lock<std::mutex> lock(wr.mutex);
                wr.cv.wait(lock,[&wr, this ](){return (!wr.queue.empty())||needStop; });
                if(!wr.queue.empty())
                {
                    auto blockPtr=wr.queue.front();
                    wr.queue.pop();
                    lock.unlock();
                    wr.worker.newBlockreceived(blockPtr);
                }
                else
                {
                    lock.unlock();
                    if(needStop){return;}
                }

            }

        }


        void loggerTask()
        {
            task<Listeners::Printer>(logger);
        }
        void fileTask()
        {
            task<Listeners::FilePrinter>(fileWorker);
        }





    private:
//Определил описание для логера и для файлов
        ProcessD<Listeners::Printer> logger;
        ProcessD<Listeners::FilePrinter> fileWorker;
//Три потока по заданию
        std::thread t1;
        std::thread t2;
        std::thread t3;

//Переменная для остановки.
        std::atomic<bool> needStop{false};

        template<class Worker>
        void pushBlock(ProcessD<Worker>& wr, std::shared_ptr<Data::Block>& block)
        {
            {
                std::lock_guard<std::mutex> lock(wr.mutex);
                wr.queue.push(block);
            }
            wr.cv.notify_all();
        }

//Создаем потоки обработчика
        CommandProcessor()
        {
            t1=std::thread(&CommandProcessor::loggerTask, this);
            t2=std::thread(&CommandProcessor::fileTask, this);
            t3=std::thread(&CommandProcessor::fileTask, this);
        }

//Тормозим потоки
        ~CommandProcessor()
        {
            needStop=true;

            logger.cv.notify_all();
            fileWorker.cv.notify_all();

            t1.join();
            t2.join();
            t3.join();
        }

        CommandProcessor(const CommandProcessor& root) = delete;
        CommandProcessor& operator=(const CommandProcessor&) = delete;
        CommandProcessor(CommandProcessor&& root) = delete;
        CommandProcessor& operator=(CommandProcessor&&) = delete;





};

#endif // COMMANDPROCESSOR_HPP
