cmake_minimum_required(VERSION 3.5)

project(OtusHomework_9_AsyncInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OtusHomework_9_AsyncInterpreter
    main.cpp

)

add_library(Async SHARED
    Async/async.h
    Async/async.cpp
    Async/ContertManager/ContextManager.hpp

    Async/Analize/Analizer.cpp
    Async/Parsing/Parser.hpp
    Async/Parsing/ParserCommand.hpp
    Async/Analize/Analizer.hpp
    Async/Data/Block.hpp
    Async/Listeners/Printer.hpp
    Async/Listeners/FilePrinter.hpp
)

target_link_libraries(OtusHomework_9_AsyncInterpreter Async)

install(TARGETS OtusHomework_9_AsyncInterpreter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
