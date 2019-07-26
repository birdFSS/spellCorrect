#pragma once

#include <sys/timerfd.h>
#include <functional>
namespace wd
{

class Timer
{
public:
    typedef std::function<void()> TimerCallBack;
    Timer(int initSec, int intervalSec, TimerCallBack cb);
    ~Timer();
    void start();
    void stop();
    int getFd() const
    { return m_timerfd; }
    void handleRead();
private:

    int createTimerfd();
    void setTimer(int initSec, int intervalSec);

private:
    int m_timerfd;
    bool m_isStarted;
    struct itimerspec m_ts;
    TimerCallBack m_cb;
};







}//end of namespace wd

