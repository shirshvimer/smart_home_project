#ifndef AGENT_FACTORY_HPP
#define AGENT_FACTORY_HPP

#include <memory>
#include <unordered_map>
#include <string>

#include "agent_interface.hpp"
#include "events_publisher.hpp"
#include "agent_generator.hpp"

namespace smart_home 
{
class AgentFactory
{
public:
    AgentFactory(std::shared_ptr<EventsPublisher> a_eventStation);
    std::shared_ptr<IAgent> Get(std::string const& a_type, std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config);
private:
    std::shared_ptr<EventsPublisher> m_eventStation;
    //std::string -> type
    std::unordered_map<std::string, std::unique_ptr<IAgentGenerator>> m_lookupMap;
};

}//smart_home

#endif /* AGENT_FACTORY_HPP */