#include "TimeWapper.h"
#include <iostream>
#include <sstream>

TimeWapper::TimeWapper()
    :ht_(std::chrono::system_clock::now())
{

}

TimeWapper::~TimeWapper()
{

}

TimeWapper::TimeWapper(uint64_t millsecond)
{
    ht_ += MILLISECONDS(millsecond);
}

time_t TimeWapper::makeEpochTime() const
{
    return std::chrono::duration_cast<SECONDS>(ht_.time_since_epoch()).count();
}

uint64_t TimeWapper::makeMillisecondTime() const
{
    return std::chrono::duration_cast<MILLISECONDS>(ht_.time_since_epoch()).count();
}

uint64_t TimeWapper::UTCTime() const
{
    return makeEpochTime() - diffTimeWithUTC();
}

TimeWapper TimeWapper::fromEpochTime(time_t tt)
{
    return TimeWapper(tt * 1000);
}

TimeWapper TimeWapper::fromUTCTime(uint64_t utct)
{
    return TimeWapper((utct + diffTimeWithUTC()) * 1000);
}

bool TimeWapper::operator==(const TimeWapper& other) const 
{
    return ht_ == other.ht_;
}

bool TimeWapper::operator!=(const TimeWapper& other) const 
{
    return !(*this  == other);
}

TimeWapper TimeWapper::timeFrom(const std::string& format,const std::string& stime)
{
    std::string tmpformat = format;
    for (auto it = tmpformat.begin(); it != tmpformat.end();it++)
    {
        if (*it != '%')
        {
            continue;
        }
        else
        {
            it++;
        }
        if (it != tmpformat.end() && (*it == 'Y' || *it == 'M' || *it == 'D'
            || *it == 'h' || *it == 'm' || *it == 's' || *it == 'S'))
        {
            *it = 'd';
        }
    }
    struct tm timeinfo;
    int year, month, day, hour, minitus, second, millsecond;
    sscanf(stime.c_str(), tmpformat.c_str(), &year, &month, &day, &hour, &minitus, &second, &millsecond);
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = minitus;
    timeinfo.tm_sec = second;

    uint64_t totalmilliseconds =  mktime(&timeinfo) * 1000 + millsecond;
    return TimeWapper(totalmilliseconds);
}

uint64_t TimeWapper::getCurrentMillSecond()
{
    return std::chrono::duration_cast<MILLISECONDS>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int TimeWapper::diffTimeWithUTC()
{
    time_t pp = time(NULL);
    struct tm ppt;
#ifdef _WIN32
	gmtime_s(&ppt, &pp);
#else
    gmtime_r(&pp, &ppt);
#endif
    auto utcpp = mktime(&ppt);
    return pp - utcpp;
}

std::string TimeWapper::timeFormat(const std::string& format,const TimeWapper& HT)
{
    uint64_t totalMilliSecond = HT.makeMillisecondTime();
    time_t totalSeconds = totalMilliSecond / 1000;
	time_t millisecondPart = totalMilliSecond % 1000;
	struct tm  timeinfo;
#ifdef _WIN32
	localtime_s(&timeinfo, &totalSeconds);
#else
	localtime_r(&totalSeconds, &timeinfo);
#endif
    std::stringstream rTime;
    for(auto it = format.cbegin(); it != format.cend();it++)
    {
        if(*it == '%')
        {
            if (++it == format.cend()) 
                break;
            switch (*it)
            {
            case 'Y': rTime << timeinfo.tm_year + 1900;
                break;
            case 'M': rTime << timeinfo.tm_mon + 1;
                break;
            case 'D': rTime << timeinfo.tm_mday;
                break;
            case 'h': rTime << timeinfo.tm_hour;
                break;
            case 'm': rTime << timeinfo.tm_min;
                break;
            case 's': rTime << timeinfo.tm_sec;
                break;
            case 'S': rTime << millisecondPart;
                break;
            default:
                rTime <<"%" << *it;
                break;
            }
        }
        else 
        {
            rTime << *it;
        }
    }
    return rTime.str();
}
 
void TimeWapper::timeFormat(const std::string& format,const TimeWapper& HT,std::ostream& os)
{
    uint64_t totalMilliSecond = HT.makeMillisecondTime();
    time_t totalSeconds = totalMilliSecond / 1000;
	time_t millisecondPart = totalMilliSecond % 1000;
	struct tm  timeinfo;
#ifdef _WIN32
	localtime_s(&timeinfo, &totalSeconds);
#else
	localtime_r(&totalSeconds, &timeinfo);
#endif
    for(auto it = format.cbegin(); it != format.cend();it++)
    {
        if(*it == '%')
        {
            if (++it == format.cend()) 
                break;
            switch (*it)
            {
            case 'Y': os << timeinfo.tm_year + 1900;
                break;
            case 'M': os << timeinfo.tm_mon + 1;
                break;
            case 'D': os << timeinfo.tm_mday;
                break;
            case 'h': os << timeinfo.tm_hour;
                break;
            case 'm': os << timeinfo.tm_min;
                break;
            case 's': os << timeinfo.tm_sec;
                break;
            case 'S': os << millisecondPart;
                break;
            default:
                os <<"%" << *it;
                break;
            }
        }
        else 
        {
            os << *it;
        }
    }
}

void TimeWapper::currentTimeFormat(char* buf,int size)
{
    TimeWapper HT;
    uint64_t totalMilliSecond = HT.makeMillisecondTime();
    time_t totalSeconds = totalMilliSecond / 1000;
	time_t millisecondPart = totalMilliSecond % 1000;
    struct tm timeinfo;
#ifdef _WIN32
	localtime_s(&timeinfo, &totalSeconds);
#else
	localtime_r(&totalSeconds, &timeinfo);
#endif
    auto loc = strftime(buf,size,"%Y-%m-%d %H:%M:%S",&timeinfo);
    sprintf(buf+loc,".%02d",millisecondPart);
}




