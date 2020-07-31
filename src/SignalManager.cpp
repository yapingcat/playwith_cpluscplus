#include "SignalManager.h"
#include <signal.h>
#include <iostream>

SignalManager& SignalManager::instance()
{
    static SignalManager s_sm;
    return s_sm;
}

void SignalManager::registerHandler(int sign,std::function<void(int)> func)
{
    handperMap_[sign] = func;
    signal(sign,SignalManager::signalHandler);
}

void SignalManager::unregisterHandler(int sign)
{
    handperMap_.erase(sign);
}


void SignalManager::signalHandler(int signo)
{
    if(SignalManager::instance().handperMap_.count(signo) != 0)
    {
        SignalManager::instance().handperMap_[signo](signo);
    }
}














