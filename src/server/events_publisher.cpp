#include "events_publisher.hpp"

namespace smart_home 
{

namespace details 
{
    using PtrAgent = std::shared_ptr<IAgent>;

    struct Creator {
        Creator(PtrAgent a_ptrAgent) : m_ptrAgent(a_ptrAgent){};
        std::vector<PtrAgent> operator()() {
            return std::vector<PtrAgent>{m_ptrAgent};
        }
    private:
        PtrAgent m_ptrAgent;
    };

    struct Updator {
        Updator(PtrAgent a_ptrAgent) : m_ptrAgent(a_ptrAgent){};
        void operator()(std::vector<PtrAgent> & a_value) {
            return a_value.push_back(m_ptrAgent);
        }
    private:
        PtrAgent m_ptrAgent;
    };
}

EventsPublisher::EventsPublisher(InterfaceSaveData& a_logStream ,size_t a_numOfThreads) 
: m_eventAgentsMapPtr(std::make_shared<EventAgentsMap>())
, m_threadsPool(std::make_shared<threads::ThreadPool>(a_numOfThreads))
, m_logStream(a_logStream)
{
}

EventsPublisher::~EventsPublisher()
{
    m_threadsPool->ShutDown();
}

void EventsPublisher::Register(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr)
{
    EventData a_key = {a_eventType, a_location};
    m_eventAgentsMapPtr->Upsert(a_key, details::Creator{a_agentPtr}, details::Updator{a_agentPtr});
}

void EventsPublisher::Unregister(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr)
{
    EventData a_key = {a_eventType, a_location};

    std::vector<PtrAgent> a_value = m_eventAgentsMapPtr->Get(a_key); //throwing exception if not find

    std::vector<PtrAgent>::iterator it = a_value.begin();
    std::vector<PtrAgent>::iterator end = a_value.end();

    while(it != end) { 
        if((**it).ID() == (*a_agentPtr).ID()) { 
            a_value.erase(it);
            break;
        }
        ++it;
    }
}

void EventsPublisher::SubmitNotify(Event const& a_event, std::shared_ptr<IEventsPublisher> a_proxy) 
{
    auto eventPtr = std::make_shared<Event>(a_event);
    m_threadsPool->AddTask(std::unique_ptr<threads::AbstractAct> {new NotifyAct{eventPtr, m_eventAgentsMapPtr, a_proxy, m_threadsPool, m_logStream}});
}

EventsPublisher::NotifyAct::NotifyAct(PtrEvent a_eventPtr, PtrEventAgentsMap a_eventAgentsMapPtr, PtrProxy a_proxyPtr, PtrThreadsPool a_threadsPool, InterfaceSaveData& a_logStream)
: m_eventPtr(a_eventPtr)
, m_eventAgentsMapPtr(a_eventAgentsMapPtr)
, m_proxyPtr(a_proxyPtr)
, m_threadsPool(a_threadsPool)
, m_logStream(a_logStream)
{
}

void EventsPublisher::NotifyAct::Act()
{
    EventData a_key = {m_eventPtr->eType, m_eventPtr->location};
    try {
        std::vector<PtrAgent> a_value = m_eventAgentsMapPtr->Get(a_key);
    
        std::vector<std::string> dataVec {m_eventPtr->eType};

        for(auto & e : m_eventPtr->payload) {
            dataVec.push_back(e);
        }

        for (auto const& agent : a_value) {
            m_threadsPool->AddTask(std::unique_ptr<threads::AbstractAct> {new InformAgentAct{m_eventPtr, agent, dataVec, m_proxyPtr}});
        }
    }
    catch (...) { 
    }
    
    m_eventPtr->Print(m_logStream);
}

EventsPublisher::InformAgentAct::InformAgentAct(PtrEvent a_eventPtr, PtrAgent a_agentsPtr, std::vector<std::string> const& a_eventData, PtrProxy a_proxyPtr)
: m_eventPtr(a_eventPtr)
, m_agentsPtr(a_agentsPtr)
, m_eventData(a_eventData)
, m_proxyPtr(a_proxyPtr)
{
}

void EventsPublisher::InformAgentAct::Act()
{
    m_agentsPtr->Act(m_eventData, m_proxyPtr);
}

}//smart_home