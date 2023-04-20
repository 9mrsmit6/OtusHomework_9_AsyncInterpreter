#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP

#include <shared_mutex>
#include <mutex>
#include <unordered_map>


//map для контекстов с блокирвкой на случай работы с одним контекстом из разных потоков
template<class Processor>
struct ContextManger
{

        static ContextManger& getInstance()
        {
            static ContextManger instance;
            return instance;
        }

        std::size_t createNewContext(std::size_t bs)
        {
            std::unique_lock<std::shared_mutex> lock(contextStorageMutex);
            auto ret=currentID;
            contextStorage.insert(std::make_pair(currentID, bs ));
            currentID++;
            return ret;
        }

        void eraseContext(std::size_t contextID)
        {
            std::unique_lock<std::shared_mutex> lock(contextStorageMutex);
            contextStorage.at(contextID).eof();
            contextStorage.erase(contextID);
        }

        auto& getContext(std::size_t contextID)
        {
           std::shared_lock<std::shared_mutex> lock(contextStorageMutex);
           return contextStorage.at(contextID);
        }

    private:
        std::shared_mutex contextStorageMutex;
        std::unordered_map<std::size_t, Processor> contextStorage{};

        std::size_t currentID{0};

        ContextManger() = default;

        ContextManger(const ContextManger& root) = delete;
        ContextManger& operator=(const ContextManger&) = delete;
        ContextManger(ContextManger&& root) = delete;
        ContextManger& operator=(ContextManger&&) = delete;

        ~ContextManger() = default;

};

#endif // CONTEXTMANAGER_HPP
