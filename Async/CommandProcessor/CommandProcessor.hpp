#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include <shared_mutex>
#include <mutex>
#include <condition_variable>

#include <queue>
#include <memory>
#include <tuple>
#include <atomic>
#include "../Data/Block.hpp"
#include "../Listeners/FilePrinter.hpp"
#include "../Listeners/Printer.hpp"
#include <thread>
#include <functional>



struct Printer
{
    Printer(const std::string s):
        str(s)
    {

    };
    ~Printer()=default;

    void newBlockreceived(std::shared_ptr<Data::Block>& job)
    {

        std::cout<<str<<std::endl;
    }

    const std::string str;
};

template <class P>
struct ProcessD
{
    std::condition_variable cv;
    std::mutex mutex;
    std::queue<std::shared_ptr<Data::Block>> queue;
    P worker;
};

struct CommandProcessor
{

        static CommandProcessor& getInstance()
        {
            static CommandProcessor instance;
            return instance;
        }

        void push(std::shared_ptr<Data::Block> block)
        {

            logger.mutex.lock();
            logger.queue.push(block);
            logger.mutex.unlock();

            logger.cv.notify_all();

            fileWorker.mutex.lock();
            fileWorker.queue.push(block);
            fileWorker.mutex.unlock();

            fileWorker.cv.notify_all();

        }

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

        ProcessD<Listeners::Printer> logger;
        ProcessD<Listeners::FilePrinter> fileWorker;

        std::thread t1;
        std::thread t2;
        std::thread t3;
        bool needStop{false};


        CommandProcessor()
        {
            t1=std::thread(&CommandProcessor::loggerTask, this);
            t2=std::thread(&CommandProcessor::fileTask, this);
            t3=std::thread(&CommandProcessor::fileTask, this);
        }

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
