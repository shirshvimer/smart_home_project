#ifndef EVENTS_PUBLISHER_HPP
#define EVENTS_PUBLISHER_HPP

#include <vector>
#include <memory>

#include "location.hpp"
#include "event.hpp"
#include "agent_interface.hpp"
#include "threads_concurrent_hash_table.hpp"
#include "threads_abstract_act.hpp"
#include "threads_thread_pool.hpp"
#include "events_publisher_interface.hpp"

namespace smart_home 
{

namespace details
{

struct HashFunc {
    std::size_t operator()(const std::pair<std::string, Location>& a_key) const
    {
        return std::hash<std::string>()(a_key.first);
    }
};

} // namespace details

class EventsPublisher : public IEventsPublisher
{
public:
    EventsPublisher(InterfaceSaveData& a_logStream ,size_t a_numOfThreads = 1);
    EventsPublisher(EventsPublisher const& a_other) = default;
    EventsPublisher& operator=(EventsPublisher const& a_other) = default;
    ~EventsPublisher();

    void Register(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) override;
    void Unregister(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) override;
    void SubmitNotify(Event const& a_event, std::shared_ptr<IEventsPublisher> a_proxy) override;

private:
    using PtrThreadsPool = std::shared_ptr<threads::ThreadPool>;
    using PtrProxy = std::shared_ptr<IEventsPublisher>;
    using EventData = std::pair<std::string, Location>;
    using PtrAgent = std::shared_ptr<IAgent>;
    using PtrEvent = std::shared_ptr<Event>;
    using EventAgentsMap = threads::ConcurrentHashTable<EventData, std::vector<PtrAgent>, details::HashFunc>;
    using PtrEventAgentsMap = std::shared_ptr<EventAgentsMap>;

    class NotifyAct : public threads::AbstractAct
    {
    public:
        NotifyAct(PtrEvent a_eventPtr, PtrEventAgentsMap a_eventAgentsMapPtr, PtrProxy a_proxyPtr, PtrThreadsPool a_threadsPool, InterfaceSaveData& a_logStream);
        NotifyAct(NotifyAct const& a_other) = default;
        NotifyAct& operator=(NotifyAct const& a_other) = default;
        virtual ~NotifyAct() = default;

        virtual void Act() override;
    private:
        PtrEvent m_eventPtr;
        PtrEventAgentsMap m_eventAgentsMapPtr;
        PtrProxy m_proxyPtr;
        PtrThreadsPool m_threadsPool;
        InterfaceSaveData& m_logStream;
    };

    class InformAgentAct : public threads::AbstractAct
    {
    public:
        InformAgentAct(PtrEvent a_eventPtr, PtrAgent a_agentsPtr, std::vector<std::string> const& a_eventData, PtrProxy a_proxyPtr);
        InformAgentAct(InformAgentAct const& a_other) = default;
        InformAgentAct& operator=(InformAgentAct const& a_other) = default;
        virtual ~InformAgentAct() = default;

        virtual void Act() override;

    private:
        PtrEvent m_eventPtr;
        PtrAgent m_agentsPtr;
        std::vector<std::string> m_eventData;
        PtrProxy m_proxyPtr;
    };

private:
    PtrEventAgentsMap m_eventAgentsMapPtr;
    PtrThreadsPool m_threadsPool;
    InterfaceSaveData& m_logStream;
};

}//smart_home

#endif /* EVENTS_PUBLISHER_HPP */