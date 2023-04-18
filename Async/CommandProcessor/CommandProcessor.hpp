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




inline void vax1(){};
struct CommandProcessor
{

        static CommandProcessor& getInstance()
        {
            static CommandProcessor instance;
            return instance;
        }

        void push(std::shared_ptr<Data::Block> block)
        {
            loggerQueueMutex.lock();
            loggerQueue.push(block);
            loggerQueueMutex.unlock();

            loggerCV.notify_all();

            fileWorkerQueueMutex.lock();
            fileWorkerQueue.push(block);
            fileWorkerQueueMutex.unlock();

            fileWorkerCV.notify_all();


        }

        template<class Worker>
        void task(Worker& worker, std::condition_variable& cv, std::queue<std::shared_ptr<Data::Block>>& q, std::mutex& m)
        {
            while(true)
            {
                std::unique_lock<std::mutex> lock(m);
                cv.wait(lock,[&q, this ](){return (!q.empty())||needStop; });
                if(!q.empty())
                {
                    auto blockPtr=q.front();
                    q.pop();
                    lock.unlock();
                    worker.newBlockreceived(blockPtr);
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
            task<Listeners::Printer>(
                        CommandProcessor::getInstance().printer,
                        CommandProcessor::getInstance().loggerCV,
                        CommandProcessor::getInstance().loggerQueue,
                        CommandProcessor::getInstance().loggerQueueMutex);
        }
        void fileTask()
        {
            task<Listeners::FilePrinter>(
                        CommandProcessor::getInstance().filePrinter,
                        CommandProcessor::getInstance().fileWorkerCV,
                        CommandProcessor::getInstance().fileWorkerQueue,
                        CommandProcessor::getInstance().fileWorkerQueueMutex);
        }





    private:
        std::condition_variable loggerCV;
        std::condition_variable fileWorkerCV;

        std::mutex loggerQueueMutex;
        std::mutex fileWorkerQueueMutex;

        std::queue<std::shared_ptr<Data::Block>> loggerQueue;
        std::queue<std::shared_ptr<Data::Block>> fileWorkerQueue;

        Listeners::Printer      printer;
        Listeners::FilePrinter  filePrinter;

        Printer pr1{"<<L>>"};
        Printer pr2{"<<F>>"};

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

            loggerCV.notify_all();
            fileWorkerCV.notify_all();

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
