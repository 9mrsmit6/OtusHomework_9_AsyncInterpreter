#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <utility>
#include <memory>
#include <ctime>



namespace Data
{
    struct Block
    {
        Block()
        {
            creationTime=std::time(nullptr);
        }

        Block(const std::size_t N):
            Block()
        {
            paylolds.reserve(N);
        }

        void push(std::unique_ptr<std::string>&& payloadPtr)
        {
            paylolds.push_back(std::forward<std::unique_ptr<std::string>>(payloadPtr));
        }

        auto begin()
        {
            return paylolds.begin();
        }

        auto end()
        {
            return paylolds.end();
        }

        std::time_t getCreationTime()
        {
            return creationTime;
        }

        auto getSize()
        {
            return paylolds.size();
        }


        private:
            std::vector<std::unique_ptr<std::string>> paylolds;
            std::size_t creationTime{0};


    };
}

#endif // BLOCK_HPP
