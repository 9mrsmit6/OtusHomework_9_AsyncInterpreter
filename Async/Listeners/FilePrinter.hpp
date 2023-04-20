#ifndef FILEPRINTER_HPP
#define FILEPRINTER_HPP

#include "Printer.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>


namespace Listeners
{
    struct FilePrinter
    {
        FilePrinter()=default;
        ~FilePrinter()=default;

        void newBlockreceived(std::shared_ptr<Data::Block>& block )
        {

            auto thID=std::rand(); //Добавил случайный постфикс

            std::stringstream fileName;
            fileName<<"bulk"<<block->getCreationTime()<<"_"<<thID<<".log";


            std::ofstream file(fileName.str(), std::ios::out);
            if(!file.is_open()){return;}

            printBlock(block, file);

            file.close();
        }
    };
}

#endif // FILEPRINTER_HPP
