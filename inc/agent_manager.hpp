#ifndef AGENT_MANAGER_HPP
#define AGENT_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include <fstream>

#include "event.hpp"
#include "agent_interface.hpp"
#include "agent_loader.hpp"
#include "events_publisher.hpp"
#include "threads_concurrent_hash_table.hpp"
#include "proxy_events_publisher.hpp"

namespace smart_home 
{
class AgentManager 
{
public:
    AgentManager(std::ifstream& a_configStream, std::shared_ptr<EventsPublisher> a_eventStation);
    AgentManager(AgentManager const& a_other) = default;
    AgentManager& operator=(AgentManager const& a_other) = default;
    ~AgentManager() = default;

    Event GetEvent(std::vector<std::string> const& a_data, std::shared_ptr<ProxyEventsPublisher>& a_eventsPublisher) const;
    
private:
    threads::ConcurrentHashTable<std::string, std::shared_ptr<IAgent>> m_agents;
};
}//smart_home

#endif /* AGENT_MANAGER_HPP */