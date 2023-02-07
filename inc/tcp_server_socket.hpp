#ifndef TCP_SERVER_SOCKET_HPP
#define TCP_SERVER_SOCKET_HPP

#include <memory>
#include <vector>

#include "exception.hpp"
#include "tcp_client_socket.hpp"


namespace net {

class ServerException: public exception::Exception  {
public:
    ServerException(const char* fn, const char* w) : Exception(fn, w) {}
};


class TCPServerSocket{
public:
    //typedef typename std::vector<int> container;
    
    TCPServerSocket(const char* a_ip, int a_port);
    TCPServerSocket(TCPServerSocket const& a_other) = delete;
    TCPServerSocket& operator=(TCPServerSocket const& a_other) = delete;
    ~TCPServerSocket();

    std::unique_ptr<TCPClientSocket> Accept();
    int Port() const;
    int Socket() const;

private:
    void Bind(const char* a_ip);
    

private:
    int m_socketNum;
    int m_port;
    //container m_clientsSockets;
};

}//net


#endif /* TCP_SERVER_SOCKET_HPP */
