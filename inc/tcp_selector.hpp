#ifndef TCP_SELECTOR_HPP
#define TCP_SELECTOR_HPP

#include <sys/select.h> /*select*/
#include <atomic>

#include "exception.hpp"
#include "tcp_client_socket.hpp"
#include "tcp_server_socket.hpp"
#include "tcp_acceptor.hpp"
#include "tcp_abstract_handler.hpp"

namespace net {

class SelectorException: public exception::Exception  {
public:
    using Exception::Exception;
};


class Selector {
public:
    Selector(TCPServerSocket& a_server, std::unique_ptr<Handler>& a_handler, std::unique_ptr<Acceptor>& a_acceptor);

    void Run();
    void Shutdown();

private:
    void Add(TCPClientSocket const& a_socket);
    void Add(TCPServerSocket const& a_socket);

    void Remove(TCPClientSocket const& a_socket);
    void Remove(TCPServerSocket const& a_socket);
    
    int Wait();

    bool IsActive(TCPClientSocket const& a_socket) const;
    bool IsActive(TCPServerSocket const& a_socket) const;

private:
    TCPServerSocket& m_server;
    std::unique_ptr<Handler>& m_handler;
    std::unique_ptr<Acceptor>& m_acceptor;
    fd_set m_master;
    fd_set m_active;
    std::atomic<bool> m_isTerminate;
};

}//net

#endif /* TCP_SELECTOR_HPP */