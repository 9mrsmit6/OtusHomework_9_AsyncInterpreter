#ifndef ASYNC_H
#define ASYNC_H

#include <string>

//Интерфейс
namespace Async
{
    std::size_t connect(std::size_t bs);
    bool disconnect(std::size_t context);
    bool receive(std::size_t context, const std::string& work);
}
#endif // ASYNC_H
