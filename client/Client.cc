#include "Client.h"

namespace wd
{
void Client::run()
{
    connectToServer();
}


void Client::connectToServer()
{
    m_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == m_fd)
    {
        perror("socket");
    }
    if(::connect(m_fd, (struct sockaddr*)m_addr.getInetAddressPtr(),sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
    }
}











}
