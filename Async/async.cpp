#include "async.h"
#include "ContertManager/ContextManager.hpp"

#include <string>
#include <iostream>

#include "Parsing/Parser.hpp"
#include "Analize/Analizer.hpp"

namespace Async
{
    using CurParser= Parsing::Parser<Analize::Analizer>;

    std::size_t connect(std::size_t bs)
    {
        std::cout<<"connect"<<std::endl;
       return ContextManger<CurParser>::getInstance().createNewContext(bs);
    }
    bool disconnect(std::size_t context)
    {
        std::cout<<"disconnect"<<std::endl;
        ContextManger<CurParser>::getInstance().eraseContext(context);
        return true;
    }
    bool receive(std::size_t context, const std::string& work)
    {
        std::cout<<"receive"<<std::endl;
        try
        {
            CurParser& obj= ContextManger<CurParser>::getInstance().getContext(context);
            obj.parse(work);
            return true;
        }
        catch(...)
        {
            return false;
        }


    }

}
