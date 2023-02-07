#include "tcp_event_handler.hpp"
#include "event.hpp"
#include "threads_abstract_act.hpp"
#include "threads_act_for_threads_pool.hpp"

namespace net 
{
EventHandler::EventHandler(std::ifstream& a_configStream, smart_home::InterfaceSaveData& a_logStream, size_t a_numOfThreads)
: m_eventPublisher(std::make_shared<smart_home::EventsPublisher>(a_logStream, a_numOfThreads))
, m_eventPublisherProxy(std::make_shared<smart_home::ProxyEventsPublisher>(m_eventPublisher))
, m_agentManager(std::make_shared<smart_home::AgentManager>(a_configStream, m_eventPublisher))
, m_protocol()
, m_threadPool(a_numOfThreads)
{
}

EventHandler::~EventHandler()
{
    m_threadPool.ShutDown();
}

std::vector<unsigned char> EventHandler::recvEntireMsg(std::shared_ptr<net::TCPClientSocket>& a_client)
{
    std::vector<unsigned char> bytesVec;
    std::vector<unsigned char> ContainerSizeRecv(sizeof(size_t));

    size_t typeSize = sizeof(char);

    ssize_t readBytes = (a_client)->Recieve(ContainerSizeRecv.data(), sizeof(size_t));

    size_t ContainerSize = m_protocol.UnPackSize(ContainerSizeRecv);

    bytesVec.resize(ContainerSize * typeSize);
    
    size_t remainBytes = ContainerSize * typeSize;

    auto* dataPtr = bytesVec.data();
    
    while(remainBytes > 0)
    {
        readBytes = (a_client)->Recieve(dataPtr, remainBytes);

        dataPtr += readBytes;
        remainBytes -= readBytes;
    }

    return bytesVec;
}

void EventHandler::HandlerIncoming(std::shared_ptr<TCPClientSocket>& a_client)
{
    std::vector<unsigned char> bytesVec = recvEntireMsg(a_client);
    
    using AbstractActPtr = std::shared_ptr<threads::AbstractAct>;
    m_threadPool.AddTask(AbstractActPtr{new threads::HandlerAct{m_eventPublisher, m_eventPublisherProxy, m_agentManager, m_protocol, bytesVec}});
}

}//net