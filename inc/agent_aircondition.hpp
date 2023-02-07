#ifndef AGENT_AIRCONDITION_HPP
#define AGENT_AIRCONDITION_HPP

#include <vector>
#include <string>

#include "agent_base.hpp"

namespace smart_home 
{
class ACAgent : public AgentBase, public std::enable_shared_from_this<ACAgent>
{
public:
    //using AgentBase::AgentBase;
    ACAgent(std::string const& a_id, Location const& a_location, std::string const& a_log, std::string const& a_config);
    virtual ~ACAgent() = default;
    virtual Event Act(std::vector<std::string> const& a_data, iagent::EventPtr a_eventsPublisher) const override;
    void Singup(std::shared_ptr<EventsPublisher> a_eventsPublisher) override;
}; 

}//smart_home

#include "inl/agent_base.hxx"

#endif /* AGENT_AIRCONDITION_HPP */