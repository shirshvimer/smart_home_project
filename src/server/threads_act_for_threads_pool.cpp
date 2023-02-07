#include <iostream>

#include "threads_act_for_threads_pool.hpp"

namespace threads {
HandlerAct::HandlerAct(std::shared_ptr<smart_home::EventsPublisher> a_eventPublisher, std::shared_ptr<smart_home::ProxyEventsPublisher> a_eventPublisherProxy, std::shared_ptr<smart_home::AgentManager> a_agentManager, smart_home::Protocol a_protocol, std::vector<unsigned char> const& a_recvBytesVec)
: m_eventPublisher(a_eventPublisher)
, m_eventPublisherProxy(a_eventPublisherProxy)
, m_agentManager(a_agentManager)
, m_protocol(a_protocol)
, m_recvBytesVec(a_recvBytesVec)
{
}

void HandlerAct::Act()
{
    auto unpackedVec = m_protocol.UnPack(m_recvBytesVec);
    
    smart_home::Event event = m_agentManager->GetEvent(unpackedVec, m_eventPublisherProxy);

    m_eventPublisher->SubmitNotify(event, m_eventPublisherProxy);
}

}//threads