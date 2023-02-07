#ifndef AGENT_DOOR_HPP
#define AGENT_DOOR_HPP

#include <vector>
#include <string>

#include "agent_base.hpp"

namespace smart_home 
{
class DoorAgent : public AgentBase, public std::enable_shared_from_this<DoorAgent>
{
public:
    DoorAgent(std::string const& a_id, Location const& a_location, std::string const& a_log, std::string const& a_config);
    virtual ~DoorAgent() = default;
    virtual Event Act(std::vector<std::string> const& a_data, iagent::EventPtr a_eventsPublisher) const override;
    void Singup(std::shared_ptr<EventsPublisher> a_eventsPublisher) override;
}; 

}//smart_home

#include "inl/agent_base.hxx"

#endif /* AGENT_DOOR_HPP */