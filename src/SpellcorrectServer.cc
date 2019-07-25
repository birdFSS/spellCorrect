#include "../include/SpellcorrectServer.h"
#include "../include/MyTask.h"
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
namespace wd
{

void SpellcorrectServer::onConnection(const wd::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl;
}

void SpellcorrectServer::onClose(const wd::TcpConnectionPtr & conn)
{
    cout << ">> " << conn->toString() << " has closed!" << endl;
}

void SpellcorrectServer::onMessage(const wd::TcpConnectionPtr & conn)
{
    //该回调函数实际不宜过长 2ms
    cout << "onMessage..." << endl;
    string msg = conn->receive();       //readline 对端需要传\n过来
    cout << ">> receive msg from client : " << msg << endl;

    wd::MyTask task(msg,conn->getPeerFd(),conn);
    m_threadpool.addTask(std::bind(&wd::MyTask::excute, &task));
}

void SpellcorrectServer::start()
{
    m_threadpool.start();
    using namespace std::placeholders;
    m_tcpServer.setConnectionCallBack(std::bind(&SpellcorrectServer::onConnection, this, _1));
    m_tcpServer.setMessageCallBack(std::bind(&SpellcorrectServer::onMessage, this, _1));
    m_tcpServer.setCloseCallBack(std::bind(&SpellcorrectServer::onClose, this, _1));
    m_tcpServer.start();

}

















}//wd

