#ifndef ANALIZER_HPP
#define ANALIZER_HPP

#include <string>
#include <utility>
#include <memory>
#include "../Parsing/ParserCommand.hpp"
#include <list>
#include "../Data/Block.hpp"
#include <iostream>
#include "../CommandProcessor/CommandProcessor.hpp"

namespace Analize
{
    //Анализатор из 7ой лабораторки
    enum class BlockAnalizeStates
    {
        Basic=0,
        StaticBlock,
        DynamicBloc,
        Skip
    };


    struct Analizer
    {

        Analizer(const std::size_t stBlockSize_):
            stBlockSize{stBlockSize_}
        {}


        void execute ( Parsing::ParseCommand cmd )
        {

            switch(currentState)
            {
                case BlockAnalizeStates::Basic:
                    currentState=handlerBasic (cmd);
                    break;

                case BlockAnalizeStates::StaticBlock:
                    currentState=handlerStaticBlock (cmd);
                    break;

                case BlockAnalizeStates::DynamicBloc:
                    currentState=handlerDynamicBlock (cmd);
                    break;

                case BlockAnalizeStates::Skip:
                    currentState=handlerSkip (cmd);
                break;

                default:
                    currentState=BlockAnalizeStates::Basic;
                    break;
            }
        }


    private:
        std::unique_ptr<Data::Block> block;
        BlockAnalizeStates currentState{BlockAnalizeStates::Basic};
        const std::size_t stBlockSize;
        std::size_t skipCnt{0};

        BlockAnalizeStates handlerBasic         ( Parsing::ParseCommand& cmd);
        BlockAnalizeStates handlerStaticBlock   ( Parsing::ParseCommand& cmd);
        BlockAnalizeStates handlerDynamicBlock  ( Parsing::ParseCommand& cmd);
        BlockAnalizeStates handlerSkip          ( Parsing::ParseCommand& cmd);


        void executeListeners()
        {
            if(block==nullptr){return;}

            CommandProcessor::getInstance().push(std::move(block));

            block=nullptr;
        }



    };
}

#endif // ANALIZER_HPP
