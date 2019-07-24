#include "TcpServer.h"
#include "Threadpool.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

wd::Threadpool * gThreadpool = nullptr;

class Task
{
public:
    Task(const string& msg, const wd::TcpConnectionPtr & conn) :
        m_msg(msg),
        m_pConn(conn)
    {

    }

    void process()
    {
        string response = m_msg;
        m_pConn->sendInLoop(response);
    }

private:
    string m_msg;
    wd::TcpConnectionPtr m_pConn;
};

void onConnection(const wd::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl;
    conn->send("welcome to server!");
}

void onClose(const wd::TcpConnectionPtr & conn)
{
    cout << ">> " << conn->toString() << " has closed!" << endl;
}

void onMessage(const wd::TcpConnectionPtr & conn)
{
    //该回调函数实际不宜过长 2ms
    cout << "onMessage..." << endl;
    string msg = conn->receive();
    cout << ">> receive msg from client : " << msg << endl;
    conn->send(msg);
    Task task(msg, conn);
    gThreadpool->addTask(std::bind(&Task::process, task));
}

int main()
{
    wd::Threadpool threadpool(4,10);
    threadpool.start();
    gThreadpool = &threadpool;
    wd::TcpServer server("192.168.4.194", 8888);
    server.setConnectionCallBack(onConnection);
    server.setMessageCallBack(onMessage);
    server.setCloseCallBack(onClose);

    server.start();
    return 0;
}

