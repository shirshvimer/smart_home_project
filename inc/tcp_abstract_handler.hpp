#ifndef TCP_ABSTRACT_HANDLER_HPP
#define TCP_ABSTRACT_HANDLER_HPP

#include <memory> //unique_ptr

#include "tcp_client_socket.hpp"

namespace net {

class Handler {
public:
    virtual ~Handler() = default;

    virtual void HandlerIncoming(std::shared_ptr<TCPClientSocket>& a_client) = 0;

protected:
    Handler() = default;
    Handler(Handler const& a_other) = default;
    Handler& operator=(Handler const& a_other) = default;
};

}//net

#endif /* TCP_ABSTRACT_HANDLER_HPP */