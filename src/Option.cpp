#include "Option.h"
#include <exception>

enum ParserState{ 
    Parser_Name,
    Parser_Value,
};

void Option::attachHandler(const std::string option, 
                    //const std::string name,
                    //const std::string& describe,
                    std::function<void(const std::string)> handler)
{
    handlerStringMap_[option] = handler;
}

void Option::parserAndHandle(int argc,char* argv[])
{
    ParserState state = Parser_Name;
    std::string param = "";
    for(int i = 1; i < argc; i++)
    {
        switch(state)
        {
        case Parser_Name:
            param = argv[i];
            if(param.front() != '-' || param.size() == 1)
                throw std::invalid_argument(std::string("Illegal Param"));
            param = param.substr(1);
            if(param == "h" || i == argc-1)
            {
                if(handlerStringMap_.count(param) == 0)
                    throw std::invalid_argument("unkown Option " + param);
                handlerStringMap_[param]("");
                break;
            }
            state = Parser_Value;
            break;
        case Parser_Value:
            std::string value = argv[i];
            if(param.front() == '-')
            {
                handlerStringMap_[param]("");
                i--; 
            }
            else
            {
                if(handlerStringMap_.count(param) == 0)
                    throw ("unkown Option " + param);
                handlerStringMap_[param](value);
            }
            state = Parser_Name;
            break;
        }
    }
}


