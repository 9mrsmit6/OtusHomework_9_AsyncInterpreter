#ifndef ASYNC_H
#define ASYNC_H

#include <iostream>
//#include "Parsing/Parser.hpp"
//#include "Analize/Analizer.hpp"
//#include "Listeners/Printer.hpp"
//#include "Listeners/FilePrinter.hpp"
#include <memory>
#include <string>


std::size_t connect();
bool disconnect(std::size_t context);
bool receive(std::size_t context, std::string& work);


#endif // ASYNC_H
