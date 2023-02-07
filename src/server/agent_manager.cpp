#include "agent_manager.hpp"

namespace smart_home
{

static threads::ConcurrentHashTable<std::string, std::shared_ptr<IAgent>> getAgents(std::ifstream& a_configStream, std::shared_ptr<EventsPublisher> a_eventPublisher)
{
    AgentLoader agentLoader{a_configStream};
    return agentLoader.Load(a_eventPublisher);
}

AgentManager::AgentManager(std::ifstream& a_configStream, std::shared_ptr<EventsPublisher> a_eventPublisher)
: m_agents(getAgents(a_configStream, a_eventPublisher))
{}

Event AgentManager::GetEvent(std::vector<std::string> const& a_data, std::shared_ptr<ProxyEventsPublisher>& a_eventsPublisher) const
{
    return m_agents.Get(a_data[0])->Act(a_data, a_eventsPublisher);
}
    
} // namespace smart_home
