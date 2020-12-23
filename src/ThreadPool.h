#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <condition_variable>
#include <vector>
#include <memory>
#include <deque>

class ThreadTask
{
public:
    ThreadTask() = default;
    ~ThreadTask() = default;

public:
    virtual int doIt() = 0;
    
};

using ThreadTaskPtr = std::shared_ptr<ThreadTask>;

class ThreadPool
{
public:
    ThreadPool(int nums);
    ~ThreadPool();

public:

    void post(ThreadTaskPtr task);

    void stop();

private:

    std::vector<std::shared_ptr<std::thread>> pool_;
    std::condition_variable cond_;
    std::mutex mtx_;
    std::deque<ThreadTaskPtr> tasks_;
    bool stop_;

};




#endif

