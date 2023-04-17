#include <iostream>
#include <memory>
#include <string>


using namespace std;

#include "Async/async.h"

int main(int argc, char *argv[])
{
//    std::size_t sz{3};
//    try
//    {
//        sz= std::stoi(argv[1]);
//    }
//    catch(...)
//    {
//        sz=3;
//        std::cout<<"static block size is wrong: 3 selected"<<std::endl;
//    }


//    if(sz<=0)
//    {
//        sz=3;
//        std::cout<<"static block size is wrong: 3 selected"<<std::endl;
//    }


//    Analize::Analizer analyzer  {sz};
//    Parsing::Parser parser      {analyzer};

//    auto consolePrinter = std::make_shared<Listeners::Printer>();
//    auto filePrinter    = std::make_shared<Listeners::FilePrinter>();


//    analyzer.addListener(consolePrinter);
//    analyzer.addListener(filePrinter);

//    parser.parse();

    std::string str{
        "2\n2\n1\n4"};

    auto c1=Async::connect(3);
//    auto c2=Async::connect();
//    auto c3=Async::connect();
//    auto c4=Async::connect();
//    auto c5=Async::connect();

    Async::receive(c1, str);
    Async::receive(c1, str);
//    Async::receive(c3, str);
//    Async::receive(c4, str);
//    Async::receive(c5, str);

    Async::disconnect(c1);
//    Async::disconnect(c2);
//    Async::disconnect(c3);
//    Async::disconnect(c4);
//    Async::disconnect(c5);


    return 0;
}
