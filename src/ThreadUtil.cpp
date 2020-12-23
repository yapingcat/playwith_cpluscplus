#include "ThreadUtil.h"
#include <sstream>

std::string getCurrentThreadId()
{
    std::stringstream ss;
    ss << std::hex << std::this_thread::get_id();
    return ss.str();
}



