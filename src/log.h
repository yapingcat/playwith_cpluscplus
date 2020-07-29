#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <sstream>
#include <functional>


#define logd(...) do { fprintf(stdout,__VA_ARGS__);fprintf(stdout,"\n");}while(0)
#define loge(...) do { fprintf(stderr,__VA_ARGS__);fprintf(stdout,"\n");}while(0)


class HappyLog
{
public:
    HappyLog(const std::string& file,int line,const std::string& levelString,int level);
    ~HappyLog();
public:
    
    HappyLog& operator<<(const std::string& str);
    HappyLog& operator<<(const char* str);  
    HappyLog& operator<<(int a);
    HappyLog& operator<<(unsigned int a);
    HappyLog& operator<<(long a);
    HappyLog& operator<<(unsigned long a);
    HappyLog& operator<<(long long a);
    HappyLog& operator<<(unsigned long long a);
    HappyLog& operator<<(float a);
    HappyLog& operator<<(double a);
    HappyLog& operator<<(bool a);

    static void setLogFunc(std::function<void(const std::string&)> func) { s_logFunc = func;}
    static void setLogLevel(int level) { s_level = level;}
    

private:
    std::stringstream cache_;
    int level_;
    static std::function<void(const std::string&)> s_logFunc;
    static int s_level;
};


#define DebugL HappyLog(__FILE__,__LINE__,"Debug",1)
#define TRACEL HappyLog(__FILE__,__LINE__,"Trace",2)
#define INFOL HappyLog(__FILE__,__LINE__,"Info",3)
#define WARNL HappyLog(__FILE__,__LINE__,"Warn",4)
#define ERRORL HappyLog(__FILE__,__LINE__,"Erroe",5)
#define FATAL HappyLog(__FILE__,__LINE__,"Fata",6)












#endif
