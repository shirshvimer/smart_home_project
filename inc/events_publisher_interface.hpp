#ifndef EVENTS_PUBLISHER_INTERFACE_HPP 
#define EVENTS_PUBLISHER_INTERFACE_HPP 

#include <memory>       // std::shared_ptr 

#include "agent_interface.hpp" 

namespace smart_home 
{ 

class IEventsPublisher 
{ 
public: 
    virtual ~IEventsPublisher() = default; 
    virtual void Register(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) = 0; 
    virtual void Unregister(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) = 0; 
    virtual void SubmitNotify(Event const& a_event, std::shared_ptr<IEventsPublisher> a_events_publisher_proxy) = 0; 

protected: 
    IEventsPublisher() = default; 
    IEventsPublisher(IEventsPublisher const& a_other) = default; 
    IEventsPublisher& operator=(IEventsPublisher const& a_other) = default; 
}; 

}//smart_home 

#endif /* EVENTS_PUBLISHER_INTERFACE_HPP  */ 