#ifndef HI_TIME_H
#define HI_TIME_H

#include <stdint.h>
#include <chrono>
#include <ratio>
#include <string>
#include <time.h>

class TimeWapper
{
public:
    using MILLISECONDS  = std::chrono::milliseconds;
    using SECONDS       = std::chrono::seconds;
    using MINUTES       = std::chrono::minutes;
    using HOURS         = std::chrono::hours;
    using DAYS          = std::chrono::duration<long long,std::ratio<86400,1>>;
public:
    TimeWapper();
    ~TimeWapper();
    TimeWapper(uint64_t millsecond);

public:
    time_t makeEpochTime() const;
    uint64_t makeMillisecondTime() const;
    uint64_t UTCTime() const;
    
public:

    bool operator==(const TimeWapper& other) const;
    bool operator!=(const TimeWapper& other) const;

public:
    static TimeWapper fromEpochTime(time_t tt);
    static TimeWapper fromUTCTime(uint64_t utct);
    
    // like "%Y-%M-%D %h:%m:%s.%S", "2013-01-31 13:52:01.123"
    static TimeWapper timeFrom(const std::string& format,const std::string& stime);
    static uint64_t getCurrentMillSecond();
    static int diffTimeWithUTC();
    static std::string timeFormat(const std::string& format,const TimeWapper& HT);
private:
    std::chrono::time_point<std::chrono::system_clock> ht_;    
};




















#endif
