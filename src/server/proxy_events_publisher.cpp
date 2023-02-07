#include "proxy_events_publisher.hpp" 

namespace smart_home 
{ 

ProxyEventsPublisher::ProxyEventsPublisher(std::shared_ptr<EventsPublisher> a_eventsPublisher) 
: m_eventsPublisher(a_eventsPublisher) 
{ 
} 

void ProxyEventsPublisher::Register(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) 
{ 
    m_eventsPublisher->Register(a_eventType, a_location, a_agentPtr); 
} 

void ProxyEventsPublisher::Unregister(std::string const& a_eventType, Location const& a_location, std::shared_ptr<IAgent> a_agentPtr) 
{ 
    m_eventsPublisher->Unregister(a_eventType, a_location, a_agentPtr); 
} 

void ProxyEventsPublisher::SubmitNotify(Event const& a_event, std::shared_ptr<IEventsPublisher> a_events_publisher_proxy) 
{ 
    m_eventsPublisher->SubmitNotify(a_event, a_events_publisher_proxy); 
} 

}//smart_home