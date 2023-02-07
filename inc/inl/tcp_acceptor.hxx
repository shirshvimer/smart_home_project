#ifndef TCP_ACCEPTOR_HXX
#define TCP_ACCEPTOR_HXX

#include "tcp_acceptor.hpp"

namespace net {

inline bool DefaultAcceptor::DoAccept(std::unique_ptr<TCPClientSocket>& a_client)
{
    return true;
}

}//net

#endif /* TCP_ACCEPTOR_HXX */