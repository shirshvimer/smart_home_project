#ifndef TCP_SERVER_SOCKER_HPP
#define TCP_SERVER_SOCKER_HPP

#include "exception.hpp"

namespace net {

class ClientException: public exception::Exception  {
public:
    using Exception::Exception;
};

class TCPClientSocket {
public:
    TCPClientSocket(const char* a_ip, int a_port);
    TCPClientSocket(int a_socket);
    TCPClientSocket(TCPClientSocket const& a_other) = delete;
    TCPClientSocket& operator=(TCPClientSocket const& a_other) = delete;
    ~TCPClientSocket();
    
    template<typename C>
    void Send( C const& a_data);

    template<typename Type>
    ssize_t Recieve(Type* a_dataPtr, size_t a_bytesToRead);

    void Close();
    int Socket() const;

private:
    void Connect(const char* a_ip, int a_port);
    
private:
    int m_socketNum;
};

}//net

#include "inl/tcp_client_socket.hxx"
#endif /* TCP_SERVER_SOCKER_HPP */
