#pragma once
#include <sys/epoll.h>
#include <vector>

namespace wd
{

class Client;
class MyEpoll
{
public:
    MyEpoll(Client& client);
    ~MyEpoll() {}

    int createEpollFd();
    void addEpollFdRead(int fd);
    void loop();
    void unloop();
    void waitEpollFd();
private:
    int m_efd;
    bool m_isLooping;
    Client & m_client;
    std::vector<struct epoll_event> m_eventList;
};







}//end of namespace wd

