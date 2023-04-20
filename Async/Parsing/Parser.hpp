#ifndef PARSER_HPP
#define PARSER_HPP

#include "../Parsing/ParserCommand.hpp"
#include <memory>
#include <iostream>
#include <sstream>
#include <utility>

namespace Parsing
{
    //Тот самый парсер из работы 7
    template<class A>
    struct Parser
    {
        Parser(std::size_t blockSize):
            analyzer{blockSize}
        {}

        void parse(const std::string& work)
        {
            std::istringstream stream(work);
            while(true)
            {
                if(stream.eof())
                {
                    return;
                }

                auto s=std::make_unique<std::string>();
                std::getline(stream, *s);

                if(*s=="")  {   continue;   }

                if(     testSimpleCmd(*s, "{", Lexeme::DynamicBlockStart)   )   {   continue;   };
                if(     testSimpleCmd(*s, "}", Lexeme::DynamicBlockStop)    )   {   continue;   };

                //тут лочить
                analyzer.execute( {  Lexeme::Command, std::move(s) }  );
                //тут разлочить

            }

        }

        void eof()
        {
           analyzer.execute( {  Lexeme::EndOfFile, nullptr } );
        }

        ~Parser()=default;
    private:
        A analyzer;

        bool  testSimpleCmd(const std::string& input, const std::string l, const Lexeme cmd)
        {
            if(input==l)
            {
                analyzer.execute(     {  cmd, nullptr }   );
                return true;
            }
            return false;
        }
    };
}

#endif // PARSER_HPP
