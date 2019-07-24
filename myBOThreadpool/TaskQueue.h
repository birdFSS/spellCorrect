#pragma once

#include "Mutexlock.h"
#include "Condition.h"
#include <queue>
#include <functional>
using std::queue;


namespace wd
{

using Task = std::function<void()>;
class TaskQueue
{
    typedef Task valueType;
public:
    TaskQueue(size_t queSize = 10);
    ~TaskQueue() {}

    bool empty() const;
    bool full() const;
    void push(valueType number);
    valueType pop();
    void wakeup();
private:
    size_t m_queSize;
    queue<valueType> m_que;
    bool m_isOpen;
    MutexLock m_mutex;
    Condition m_notFull;
    Condition m_notEmpty;
};







}//end of namespace wd

