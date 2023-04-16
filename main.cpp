#include <iostream>
#include "Parsing/Parser.hpp"
#include "Analize/Analizer.hpp"
#include "Listeners/Printer.hpp"
#include "Listeners/FilePrinter.hpp"
#include <memory>
#include <string>


using namespace std;



int main(int argc, char *argv[])
{
    std::size_t sz{3};
    try
    {
        sz= std::stoi(argv[1]);
    }
    catch(...)
    {
        sz=3;
        std::cout<<"static block size is wrong: 3 selected"<<std::endl;
    }


    if(sz<=0)
    {
        sz=3;
        std::cout<<"static block size is wrong: 3 selected"<<std::endl;
    }


    Analize::Analizer analyzer  {sz};
    Parsing::Parser parser      {analyzer};

    auto consolePrinter = std::make_shared<Listeners::Printer>();
    auto filePrinter    = std::make_shared<Listeners::FilePrinter>();


    analyzer.addListener(consolePrinter);
    analyzer.addListener(filePrinter);

    parser.parse();

    return 0;
}
