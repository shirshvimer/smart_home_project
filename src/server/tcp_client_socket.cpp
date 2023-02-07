#include <sys/socket.h>
#include <netinet/in.h> /*struct sockaddr_in*/
#include <unistd.h> /*close*/
#include <stdexcept> /*except*/
#include <string.h> /*string.h*/
#include <arpa/inet.h>  /*inet*/

#include "tcp_client_socket.hpp"

namespace net {

TCPClientSocket::TCPClientSocket(const char* a_ip, int a_port)
: m_socketNum(socket(AF_INET, SOCK_STREAM, 0))
{
    if (m_socketNum < 0)
    {
        throw ClientException("socket", "create client failed");
    }

    Connect(a_ip, a_port);
}

TCPClientSocket::TCPClientSocket(int a_socket)
: m_socketNum(a_socket)
{
}

TCPClientSocket::~TCPClientSocket()
{
    close(m_socketNum);
}

void TCPClientSocket::Connect(const char* a_ip, int a_port)
{
    struct sockaddr_in sin;
    memset(&sin, 0 ,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(a_ip);
    sin.sin_port = htons(a_port);
    if (connect(m_socketNum, (struct sockaddr*)&sin, sizeof(sin)) < 0)
    {
        throw ClientException("connect", "connect failed");
    }
}

void TCPClientSocket::Close() 
{
    close(m_socketNum);
}

}//net