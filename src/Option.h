#ifndef OPTION_H
#define OPTION_H

#include <tuple>
#include <unordered_map>
#include <string>
#include <functional>
#include <algorithm>

class Option
{
public:
    Option() = default;
    ~Option() default;

public:
    void parserAndHandle(int argc,char* argv[]);

    void attachHandler(const std::string option, 
                        //const std::string name,
                        //const std::string& describe,
                        std::function<void(const std::string)> handler);

    //TODO
    //std::string formatToString();

private:
    std::unordered_map<std::string,std::function<void(const std::string)>> handlerStringMap_;

};








#endif