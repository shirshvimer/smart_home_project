#ifndef AGENT_BASE_HPP
#define AGENT_BASE_HPP

#include <vector>
#include <string>
#include <iostream>

#include "events_publisher.hpp"
#include "agent_interface.hpp"
#include "events_publisher_interface.hpp"

namespace smart_home 
{
class AgentBase : public IAgent
{
public:
    virtual ~AgentBase() = default;
    virtual Event Act(std::vector<std::string> const& a_data, iagent::EventPtr a_eventsPublisher) const = 0;
    virtual std::string ID() const override;
    virtual void Singup(std::shared_ptr<EventsPublisher> a_eventsPublisher);
    
protected:
    AgentBase(std::string const& a_id, Location const& a_location, std::string const& a_log, std::string const& a_config);

protected:
    std::string m_id;
    Location m_location;
    std::string m_log;
    std::string m_config;
}; 

}//smart_home

#include "inl/agent_base.hxx"

#endif /* AGENT_BASE_HPP */