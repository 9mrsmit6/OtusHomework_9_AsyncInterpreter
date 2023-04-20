#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "../Data/Block.hpp"
#include <iostream>

namespace Listeners   //Так было в прошлой работе
{
    //Печать из 7 ой лабы. Я попробовал реализовать через оператор << Здесь просто оригинальный вариант
    template <class Stream>
    void printBlock(std::shared_ptr<Data::Block>& block, Stream& stream)
    {
        stream<<"bulk: ";

        bool isFirst{true};

        for(auto& v:(*block))
        {

            if(!isFirst){     stream<<", ";         }
            else        {     isFirst=false;        }

            stream<<(*v);
        }
    }

    struct Printer
    {
        Printer()=default;
        ~Printer()=default;

        void newBlockreceived(std::shared_ptr<Data::Block>& block)
        {
            printBlock(block, std::cout);
            std::cout<<std::endl;
        }
    };


}
#endif // PRINTER_HPP
