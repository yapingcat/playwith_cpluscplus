#include "ThreadPool.h"
#include <iostream>
#include <memory>

std::unique_ptr

ThreadPool::ThreadPool(int nums)
    :stop_(false)
{
    for(int i = 0; i < nums; i++)
    {
        auto thread = std::make_shared<std::thread>([this](){
            
            while(!stop_)
            {
                ThreadTaskPtr task;
                {
                    std::unique_lock<std::mutex> guard(mtx_);
                    cond_.wait(guard,[this](){
                        return stop_ || !tasks_.empty();
                    });
                    if(stop_)
                        break;
                    task = tasks_.front();
                    tasks_.pop_front();
                }
                task->doIt();
            }
            std::cout<<"quit thread"<<std::endl;
        });
        pool_.push_back(thread);
    }
}

ThreadPool::~ThreadPool()
{
    stop();
    for(auto&& thread : pool_)
    {
        thread->join();
    }
}

void ThreadPool::post(ThreadTaskPtr task)
{
    std::unique_lock<std::mutex> guard(mtx_);
    tasks_.push_back(task);
    cond_.notify_one();
}

void ThreadPool::stop()
{
    stop_ = true;
    cond_.notify_all();
}



#ifdef TEST

#include <iostream>
#include <random>
#include "ThreadUtil.h"

class TestTask : public ThreadTask
{
public:
    int doIt()
    {
        static std::default_random_engine engine(time(NULL));
        static std::uniform_int_distribution<int> di(10,20);
        std::cout<<"["<<getCurrentThreadId()<<"] "<< a << " this is my test task" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(di(engine)));
        return 0;
    }

    int a;
};

int main()
{
    int b = 0;
    ThreadPool tp(4);
    for(int i = 0; i < 100 ;i ++)
    {
        auto ts = std::make_shared<TestTask>();
        ts->a = b++;
        tp.post(ts);
    }

    getchar();
    
    
    for(int i = 0; i < 4 ;i ++)
    {
        auto ts = std::make_shared<TestTask>();
        ts->a = b++;
        tp.post(ts);
    }

    getchar();
}





#endif


