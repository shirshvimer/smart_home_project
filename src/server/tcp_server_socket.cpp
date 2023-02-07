#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*struct sockaddr_in*/
#include <unistd.h> /*close*/
#include <stdexcept> /*except*/
#include <string.h> /*string.h*/
#include <arpa/inet.h> /*inet*/

#include "tcp_server_socket.hpp"

namespace net {

void TCPServerSocket::Bind(const char* a_ip)
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(a_ip);
    sin.sin_port = htons(m_port);

    if (bind(m_socketNum, (struct sockaddr*)&sin, sizeof(sin)) < 0)
    {
        throw ServerException("Bind", "bind failed");
    }
}

TCPServerSocket::~TCPServerSocket()
{
    close(m_socketNum);
}

TCPServerSocket::TCPServerSocket(const char* a_ip, int a_port)
: m_socketNum(socket(AF_INET, SOCK_STREAM, 0))
, m_port(a_port)
{
    if (m_socketNum < 0)
    {
        throw ServerException("socket", "create client failed");
    }
    
    int optval = 1;
    if (setsockopt(m_socketNum, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval)) < 0)
    {
        throw ServerException("setsockopt", "setsockopt failed");
    }

    Bind(a_ip);

    if (listen(m_socketNum, 50) < 0)
    {
        throw ServerException("listen", "listen failed");
    }
}

std::unique_ptr<TCPClientSocket> TCPServerSocket::Accept()
{
    struct sockaddr_in client_sin;
    int addr_len = sizeof(client_sin);
    int clientSock = accept(m_socketNum, (struct sockaddr *) &client_sin, (socklen_t *)&addr_len);

    if (clientSock < 0 )
    {
        throw ServerException("accept", "accept failed");
    }

    return std::unique_ptr<TCPClientSocket>{new TCPClientSocket{clientSock}};
}

int TCPServerSocket::Port() const
{
    return m_port;
}

int TCPServerSocket::Socket() const
{
    return m_socketNum;
}


}//net