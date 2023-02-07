#include "agent_door.hpp"

namespace smart_home
{

static std::string timePointAsString(std::chrono::system_clock::time_point const& a_timePoint) { 
    std::time_t systemTime = std::chrono::system_clock::to_time_t(a_timePoint); 
    std::string timeString = std::ctime(&systemTime); 
    timeString.resize(timeString.size()-1); 
    
    return timeString; 
} 

DoorAgent::DoorAgent(std::string const& a_id, Location const& a_location, std::string const& a_log, std::string const& a_config)
: AgentBase::AgentBase(a_id, a_location, a_log, a_config)
{
}

Event DoorAgent::Act(std::vector<std::string> const& a_data, iagent::EventPtr a_eventsPublisher) const
{
    Event event;
    
    event.timestamp = timePointAsString(std::chrono::system_clock::now());
    event.eType = "CONTROLLER_DOOR";
    event.location = m_location;
    event.payload.push_back("Lock_OK");

    a_eventsPublisher->SubmitNotify(event, a_eventsPublisher);

    return event;
}

void DoorAgent::Singup(std::shared_ptr<EventsPublisher> a_eventsPublisher)
{
    a_eventsPublisher->Register("ENTRANCE_REQUEST", m_location, shared_from_this());
}

} // namespace smart_home