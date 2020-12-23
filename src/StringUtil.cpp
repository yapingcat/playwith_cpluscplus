#include "StringUtil.h"
#include <algorithm>
#include <cstring>

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
    if(pre != str.end())
    {
        auto distanceFromBegin = std::distance(str.begin(),pre);
        auto len = std::distance(pre,str.end());
        func(str.c_str() + distanceFromBegin,len);
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
    if(pre != str.end())
    {
        auto distanceFromBegin = std::distance(str.begin(),pre);
        auto len = std::distance(pre,str.end());
        func(str.c_str() + distanceFromBegin,len);
    }
}

int splitInTwoPart(const std::string& str,const char c, std::string& left, std::string& right)
{
    left = "";
    right = "";
    auto splitloc = str.find(c);
    if(splitloc == std::string::npos)
    {
        left = str;
        return 0;
    }
    left = str.substr(0,splitloc);
    right = str.substr(splitloc + 1);
    auto found = left.find_last_not_of(' ');
    if(found != std::string::npos)
        left.erase(found+1);
    found = right.find_first_not_of(' ');
    if(found != std::string::npos)
        right = right.substr(found);
}

bool startWithString(const std::string& str, const std::string& startStr)
{
    if(start.size() > str.size())
        return false;
    return std::equal(startStr.begin(),startStr.end(),str.begin());
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

void readLines(const std::string& str,const std::function<void(const char*,size_t)>& func)
{
    std::string::size_type loc = 0;
    for(std::string::size_type i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if(c == '\r' || c == '\n')
        {
            if(i - loc > 0)
            {
                func(str.c_str() + loc,i - loc);
            }
            loc = i + 1;
        }
    }
}

#ifdef STRINGUTIL_TEST
#include <iostream>
using namespace std;

int main()
{
    std::string test{"zs_cyp_love_forever"};
    splitString(test,'_',[](const char* s,size_t len){
                string ret(s,len);
                std::cout<<ret<<" "<<len<<endl;
            });
    
    splitString(test,'r',[](const char* s,size_t len){
                string ret(s,len);
                std::cout<<ret<<" "<<len<<endl;
            });

    splitString(test,{'r','_'},[](const char* s,size_t len){
                string ret(s,len);
                std::cout<<ret<<" "<<len<<endl;
            });
    
    auto ret = splitString(test,'_');
    for(auto&& s : ret)
        cout<<s<<endl;

    auto ret2 = splitString(test,{'r','_'});
    for(auto&& s: ret2)
        cout<<s<<endl;
    return 0;
}



#endif





