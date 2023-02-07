#include "event.hpp"
#include "agent_aircondition.hpp"

namespace smart_home
{

static std::string timePointAsString(std::chrono::system_clock::time_point const& a_timePoint) { 
    std::time_t systemTime = std::chrono::system_clock::to_time_t(a_timePoint); 
    std::string timeString = std::ctime(&systemTime); 
    timeString.resize(timeString.size()-1); 
    
    return timeString; 
} 

ACAgent::ACAgent(std::string const& a_id, Location const& a_location, std::string const& a_log, std::string const& a_config)
: AgentBase::AgentBase(a_id, a_location, a_log, a_config)
{}

Event ACAgent::Act(std::vector<std::string> const& a_data, iagent::EventPtr a_eventsPublisher) const
{
    Event event;
    int tempature = stoi(a_data[1]);
    event.timestamp = timePointAsString(std::chrono::system_clock::now());
    event.location = m_location;
    event.payload = a_data;
    if(tempature > 27) {
        event.eType = "CONTROLLER_AC_ON";
    } 
    else if(tempature < 22) {
        event.eType = "CONTROLLER_AC_OFF";
    }
    else {
        event.eType = "CONTROLLER_AC_NO_CHANGE";
    }

    a_eventsPublisher->SubmitNotify(event, a_eventsPublisher);
    
    return event;
}

void ACAgent::Singup(std::shared_ptr<EventsPublisher> a_eventsPublisher)
{
    a_eventsPublisher->Register("TEMP_LEVEL", m_location, shared_from_this());
}

} // namespace smart_home