#ifndef TCP_ACCEPTOR_HPP
#define TCP_ACCEPTOR_HPP

#include <memory> /*unique_ptr*/

#include "tcp_client_socket.hpp"

namespace net {

class Acceptor {
public:
    virtual ~Acceptor() = default;
    virtual bool DoAccept(std::unique_ptr<TCPClientSocket>& a_client) = 0;

protected:
    Acceptor() = default;
    Acceptor(Acceptor const& a_other) = default;
    Acceptor& operator=(Acceptor const& a_other) = default;
};

class DefaultAcceptor : public Acceptor{
public:
    DefaultAcceptor() = default;
    bool DoAccept(std::unique_ptr<TCPClientSocket>& a_client) override;
};

}//net

#include "inl/tcp_acceptor.hxx"

#endif /* TCP_ACCEPTOR_HPP */