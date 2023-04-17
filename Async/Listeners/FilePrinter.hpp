#ifndef FILEPRINTER_HPP
#define FILEPRINTER_HPP

#include "Printer.hpp"
#include <fstream>
#include <string>
#include <sstream>

namespace Listeners
{
    struct FilePrinter: public Analize::AnalizerListener
    {
        FilePrinter()=default;
        ~FilePrinter()=default;

        void newBlockreceived(std::shared_ptr<Data::Block> block) override
        {
            std::stringstream fileName;
            fileName<<"bulk"<<block->getCreationTime()<<".log";


            std::ofstream file(fileName.str(), std::ios::out);
            if(!file.is_open()){return;}

            printBlock(block, file);

            file.close();
        }
    };
}

#endif // FILEPRINTER_HPP
