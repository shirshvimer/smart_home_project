#include <sys/socket.h> 
#include <netinet/in.h> /*struct sockaddr_in*/
#include <unistd.h> /*close*/
#include <stdexcept> /*except*/
#include <string.h> /*string.h*/
#include <arpa/inet.h> /*inet*/
#include <iostream>
#include <vector>

#include "tcp_client_socket.hpp"

namespace net {

template<typename C>
void TCPClientSocket::Send(C const& a_data)
{
    size_t dataSize = a_data.size();

    auto* dataPtr = a_data.data();
    int remainBytes = dataSize * sizeof(typename C::value_type);

    while(remainBytes > 0)
    {
        ssize_t sentBytes = send(m_socketNum, dataPtr ,remainBytes , 0);
        if (sentBytes < 0) 
        {
            throw ClientException("send", "send failed");
        }

        dataPtr += sentBytes / sizeof(typename C::value_type);
        remainBytes -= sentBytes;
    }
}

static void checkReadBytes(ssize_t a_readBytes) 
{
    if (a_readBytes == 0) 
    { 
        throw ClientException("Recieve", "recv failed");
    } 
    
    else if (a_readBytes < 0 )
    { 
        throw ClientException("Recieve", "recv failed");
    }
}

template<typename Type>
ssize_t TCPClientSocket::Recieve(Type* a_dataPtr, size_t a_bytesToRead)
{
    ssize_t readBytes = recv(m_socketNum, a_dataPtr, a_bytesToRead,0);
    checkReadBytes(readBytes);
    
    return readBytes;
}

inline int TCPClientSocket::Socket() const
{
    return m_socketNum;
}

}//net