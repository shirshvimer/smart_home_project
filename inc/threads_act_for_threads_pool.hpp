#ifndef THREADS_ACT_FOR_THREADS_POOL_HPP
#define THREADS_ACT_FOR_THREADS_POOL_HPP

#include "threads_abstract_act.hpp"
#include "tcp_client_socket.hpp"
#include "events_publisher.hpp"
#include "protocol.hpp"
#include "agent_manager.hpp"
#include "save_data_interface.hpp"

namespace threads {

class HandlerAct : public AbstractAct{
public:
    using PtrTCPClient = std::shared_ptr<net::TCPClientSocket>;
    HandlerAct(std::shared_ptr<smart_home::EventsPublisher> a_eventPublisher, std::shared_ptr<smart_home::ProxyEventsPublisher> a_eventPublisherProxy, std::shared_ptr<smart_home::AgentManager> a_agentManager, smart_home::Protocol a_protocol, std::vector<unsigned char> const& a_recvBytesVec);

    virtual void Act() override;

private:
    std::shared_ptr<smart_home::EventsPublisher> m_eventPublisher;
    std::shared_ptr<smart_home::ProxyEventsPublisher> m_eventPublisherProxy;
    std::shared_ptr<smart_home::AgentManager> m_agentManager;
    smart_home::Protocol m_protocol; 
    std::vector<unsigned char> m_recvBytesVec;
};

}//threads

#endif /* THREADS_ACT_FOR_THREADS_POOL_HPP */