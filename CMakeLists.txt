cmake_minimum_required(VERSION 3.5)

project(OtusHomework_9_AsyncInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( Threads )

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
    Async/CommandProcessor/CommandProcessor.hpp
)

target_link_libraries( Async ${CMAKE_THREAD_LIBS_INIT} )

target_link_libraries(OtusHomework_9_AsyncInterpreter ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(OtusHomework_9_AsyncInterpreter Async)

install(TARGETS OtusHomework_9_AsyncInterpreter Async
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME   "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_CONTACT 9mrsmit6@gmail.com)
include(CPack)
