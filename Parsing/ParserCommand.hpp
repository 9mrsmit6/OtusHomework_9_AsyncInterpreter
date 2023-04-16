#ifndef PARSERCOMMAND_HPP
#define PARSERCOMMAND_HPP


#include <string>
#include <utility>
#include <memory>
#include <tuple>

namespace Parsing
{
    enum class Lexeme
    {
        Command,
        DynamicBlockStart,
        DynamicBlockStop,
        EndOfFile
    };

    using ParseCommand = std::tuple<Lexeme, std::unique_ptr<std::string>>;

}


#endif // PARSERCOMMAND_HPP
