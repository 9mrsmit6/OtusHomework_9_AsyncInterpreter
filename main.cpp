#include <iostream>
#include <string>
#include <thread>
#include <sstream>

#include "Async/async.h"

//Печать динамического блока
//Можно в одну строку все запихнуть. Без разницы
void sendStaticBlock(const std::size_t cont, std::size_t len, std::string base)
{
    for(std::size_t i{0};i!=len;i++)
    {
        std::stringstream buf;
        buf<<base<<i<<std::endl;
        Async::receive(cont, buf.str());
    }
}

//Печать статического блока
void sendDynamicBlock(const std::size_t cont, std::size_t len)
{
    Async::receive(cont, "{");
    sendStaticBlock(cont, len, "dynamicCmd");
    Async::receive(cont, "}");
}

//Метод потока который создает контекст выполняет работу и удаляет его
void worker()
{
   auto context=Async::connect(3);
   for(std::size_t i{0};i!=1000;i++)
   {
       sendStaticBlock(context,11,"staticCmd");
       sendDynamicBlock(context,10);
   }
   Async::disconnect(context);
}

int main(int argc, char *argv[])
{
//Делаем потоки
    auto t1=std::thread(worker);
    auto t2=std::thread(worker);
    auto t3=std::thread(worker);
    auto t4=std::thread(worker);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
