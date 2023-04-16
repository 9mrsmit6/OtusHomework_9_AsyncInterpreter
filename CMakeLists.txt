cmake_minimum_required(VERSION 3.5)

project(OtusHomework_9_AsyncInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OtusHomework_9_AsyncInterpreter
    main.cpp
    Analize/Analizer.cpp
    Parsing/Parser.hpp
    Parsing/ParserCommand.hpp
    Analize/Analizer.hpp
    Data/Block.hpp
    Listeners/Printer.hpp
    Listeners/FilePrinter.hpp
)

add_library(Async SHARED
    Async/async.h
    Async/async.cpp
)

install(TARGETS OtusHomework_9_AsyncInterpreter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
