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





