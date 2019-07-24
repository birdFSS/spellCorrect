#pragma once
#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Noncopyable.h"
#include <functional>
#include <string>
#include <memory>
using std::string;
namespace wd
{
class TcpConnection;
class EventLoop;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallBack = std::function<void(const TcpConnectionPtr&)>;

class TcpConnection :
    Noncopyable,
    public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd, EventLoop *); 
    ~TcpConnection();

    string receive();
    void send(const string& msg);
    void sendInLoop(const string &msg);

    string toString() const;                       
    void shutdown();

    void setConnectionCallBack(const TcpConnectionCallBack & cb)
    { m_onConnection = std::move(cb); }
    void setMessageCallBack(const TcpConnectionCallBack & cb)
    { m_onMessage= std::move(cb); }
    void setCloseCallBack(const TcpConnectionCallBack & cb)
    { m_onClose= std::move(cb); }

    void handleConnectionCallBack();
    void handleMessageCallBack();
    void handleCloseCallBask();
private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
private:
    Socket m_sock;
    SocketIO m_socketIO;
    InetAddress m_localAddr;
    InetAddress m_peerAddr;
    bool m_isShutdownWrite;
    EventLoop * m_loop;

    //单个Tcp连接的回调函数
    TcpConnectionCallBack m_onConnection;
    TcpConnectionCallBack m_onMessage;
    TcpConnectionCallBack m_onClose;
};







}//end of namespace wd

