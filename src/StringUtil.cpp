#include "StringUtil.h"
#include <algorithm>

void splitString(const std::string& str,char c,std::function<void(const char*,size_t)> func)
{
    auto pre = str.begin();
    for(auto&& it = str.begin();it != str.end(); it++)
    {
        if(*it == c)
        {
            auto distanceFromBegin = std::distance(str.begin(),pre);
            auto len = std::distance(pre,it);
            if(len > 0)
                func(str.c_str() + distanceFromBegin,len);
            pre = it + 1;
        }
    }
}

void splitString(const std::string& str,const std::vector<char>& vc,std::function<void(const char*,size_t)> func)
{
    auto pre = str.begin();
    for(auto&& it = str.begin();it != str.end(); it++)
    {
        if(std::find(vc.begin(),vc.end(),*it) != vc.end())
        {
            auto distanceFromBegin = std::distance(str.begin(),pre);
            auto len = std::distance(pre,it);
            if(len > 0)
                func(str.c_str() + distanceFromBegin,len);
            pre = it + 1;
        }
    }
}

std::vector<std::string> splitString(const std::string& str,char c)
{
    std::vector<std::string> result;
    splitString(str,c,[&result](const char* s,size_t len){
        result.emplace_back(s,len);
    });
    return result;
}

std::vector<std::string> splitString(const std::string& str,const std::vector<char>& vc)
{
    std::vector<std::string> result;
    splitString(str,vc,[&result](const char* s,size_t len){
        result.emplace_back(s,len);
    });
    return result;
}







