#ifndef PARSER_HPP
#define PARSER_HPP

#include "ParserCommand.hpp"
#include <memory>
#include <iostream>
#include <utility>

namespace Parsing
{
    template<class A>
    struct Parser
    {
        Parser(A& analyzer_):
            analyzer{analyzer_}
        {}

        void parse()
        {

            while(true)
            {
                if(std::cin.eof())
                {
                    analyzer.execute( {  Lexeme::EndOfFile, nullptr } );
                    return;
                }

                auto s=std::make_unique<std::string>();
                std::getline(std::cin, *s);

                if(*s=="")  {   continue;   }

                if(     testSimpleCmd(*s, "{", Lexeme::DynamicBlockStart)   )   {   continue;   };
                if(     testSimpleCmd(*s, "}", Lexeme::DynamicBlockStop)    )   {   continue;   };

                analyzer.execute( {  Lexeme::Command, std::move(s) }  );

            }

        }

        ~Parser()=default;
    private:
        A& analyzer;

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
