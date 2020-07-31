#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <unordered_map>


//not thread safe
class SignalManager
{
public:
    static SignalManager& instance();

    void registerHandler(int sign,std::function<void(int)> func);

    void unregisterHandler(int sign);

protected:
    SignalManager() = default;
    ~SignalManager() = default;

private:

    static void signalHandler(int signo);

private:

    std::unordered_map<int,std::function<void(int)>> handperMap_;
    
};











#endif






