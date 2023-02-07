#ifndef AGENT_INTERFACE_HPP
#define AGENT_INTERFACE_HPP

#include <vector>
#include <string>
#include <memory>

#include "event.hpp"
//#include "events_publisher.hpp"
//#include "proxy_events_publisher.hpp"

namespace smart_home 
{

class EventsPublisher;
class IEventsPublisher;

namespace iagent
{
    using EventPtr = std::shared_ptr<IEventsPublisher>;
} // namespace iagent

class IAgent 
{
public:
    virtual ~IAgent() = default;
    virtual Event Act(std::vector<std::string> const& a_data, iagent::EventPtr a_eventsPublisher) const = 0;
    virtual std::string ID() const = 0;
    virtual void Singup(std::shared_ptr<EventsPublisher> a_eventsPublisher) = 0;

protected:
    IAgent() = default;
    IAgent(IAgent const& a_other) = default;
    IAgent& operator=(IAgent const& a_other) = default;
}; 

}//smart_home

#endif /* AGENT_INTERFACE_HPP */