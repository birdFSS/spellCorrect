#pragma once
#include "TaskQueue.h"
#include <cstdio>
#include <vector>
#include <memory>
#include <functional>

namespace wd
{

class Thread;

class Threadpool
{
    friend class MyThread;
public:
    typedef std::function<void()> ElemType;
    typedef std::function<void()> Task;
    Threadpool(size_t threadNum = 4, size_t queSize = 10);
    ~Threadpool();

    void start();
    void addTask(ElemType elem);
    void stop();
private:
    ElemType getTask();
    void threadFunc();
private:
    size_t m_queSize;
    size_t m_threadNum;
    bool m_isExit;
    TaskQueue m_taskqueue;
    std::vector<std::unique_ptr<Thread>> m_threads;
};







}//end of namespace wd

