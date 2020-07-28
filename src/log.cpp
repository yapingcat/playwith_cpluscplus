#include "log.h"
#include "TimeWapper.h"
#include <thread>


std::function<void(const std::string&)> HappyLog::s_logFunc;
int HappyLog::s_level = 1;


HappyLog::HappyLog(const std::string& file,int line,const std::string& levelString,int level)
    :level_(level)
{
    TimeWapper now;
    cache_.precision(4);
    cache_<<TimeWapper::timeFormat("%Y-%M-%D %h:%m:%s.%S ",now)<<"["<<levelString<<"]" 
          <<"[" <<std::hex<<std::showbase<<std::this_thread::get_id()<<"]"<<std::dec
          <<"["<<file<<":"<<line<<"]";
}

HappyLog::~HappyLog()
{
    cache_ <<'\n';
    if(s_logFunc && level_ >= s_level)
        s_logFunc(cache_.str());
}

HappyLog& HappyLog::operator<<(const std::string& str)
{
    cache_ << str;
    return *this;
}

HappyLog& HappyLog::operator<<(const char* str)
{
    cache_ << str;
    return *this;
}

HappyLog& HappyLog::operator<<(int a)
{
    cache_<<std::dec<<a;
    return *this;
}

HappyLog& HappyLog::operator<<(unsigned int a)
{
    cache_<<std::dec<<a;
    return *this;
}
 
HappyLog& HappyLog::operator<<(long a)
{
    cache_<<std::dec<<a;
    return *this;
}


HappyLog& HappyLog::operator<<(unsigned long a)
{
    cache_<<std::dec<<a;
    return *this;
}
    
HappyLog& HappyLog::operator<<(long long a)
{
    cache_<<std::dec<<a;
    return *this;
}

HappyLog& HappyLog::operator<<(unsigned long long a)
{
    cache_<<std::dec<<a;
    return *this;
}

HappyLog& HappyLog::operator<<(float a)
{
    cache_<< a <<std::fixed;
    return *this;
}

HappyLog& HappyLog::operator<<(double a)
{
    cache_<< a <<std::fixed;
    return *this;
}

HappyLog& HappyLog::operator<<(bool a)
{
    cache_<<std::boolalpha<<a<<std::noboolalpha;
    return *this;
}


