#ifndef PROXY_EVENTS_PUBLISHER_HPP 
#define PROXY_EVENTS_PUBLISHER_HPP 

#include <memory>       // std::shared_ptr 

#include "events_publisher_interface.hpp" 
#include "events_publisher.hpp" 

namespace smart_home 
{ 

class ProxyEventsPublisher : public IEventsPublisher, std::enable_shared_from_this<ProxyEventsPublisher>
{
public: 
    ProxyEventsPublisher(std::shared_ptr<EventsPublisher> a_eventsPublisher); 
    ProxyEventsPublisher(ProxyEventsPublisher const& a_other) = default; 
    ProxyEventsPublisher& operator=(ProxyEventsPublisher const& a_other) = default; 
    ~ProxyEventsPublisher() = default; 

    virtual void Register(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) override; 
    virtual void Unregister(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) override; 
    virtual void SubmitNotify(Event const& a_event, std::shared_ptr<IEventsPublisher> a_events_publisher_proxy) override; 
    
private: 
    std::shared_ptr<EventsPublisher> m_eventsPublisher; 
}; 

}//smart_home 

#endif /* PROXY_EVENTS_PUBLISHER_HPP */ 