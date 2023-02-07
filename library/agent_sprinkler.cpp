#include "agent_sprinkler.hpp"

namespace smart_home
{

static std::string timePointAsString(std::chrono::system_clock::time_point const& a_timePoint) { 
    std::time_t systemTime = std::chrono::system_clock::to_time_t(a_timePoint); 
    std::string timeString = std::ctime(&systemTime); 
    timeString.resize(timeString.size()-1); 
    
    return timeString; 
} 
    
SprinklerAgent::SprinklerAgent(std::string const& a_id, Location const& a_location, std::string const& a_log, std::string const& a_config)
: AgentBase::AgentBase(a_id, a_location, a_log, a_config)
{}

Event SprinklerAgent::Act(std::vector<std::string> const& a_data, iagent::EventPtr a_eventsPublisher) const
{
    Event event;

    event.timestamp = timePointAsString(std::chrono::system_clock::now());
    event.location = m_location;
    event.payload = a_data;

    if(a_data[0] == "FIRE") {
        if(a_data[1] == "SIG_NO_FIRE") {
            event.eType = "CONTROLLER_SPRINKLER_OFF";
        }
        else {
            event.eType = "CONTROLLER_SPRINKLER_ON";
        }
    }
    else {
        int tempature = stoi(a_data[1]);
        if(tempature > 68) {
            event.eType = "CONTROLLER_SPRINKLER_ON";
        }
        else {
            event.eType = "CONTROLLER_SPRINKLER_OFF";
        }
    }

    a_eventsPublisher->SubmitNotify(event, a_eventsPublisher);

    return event;
}

void SprinklerAgent::Singup(std::shared_ptr<EventsPublisher> a_eventsPublisher)
{
    a_eventsPublisher->Register("FIRE", m_location, shared_from_this());
    a_eventsPublisher->Register("TEMP_LEVEL", m_location, shared_from_this());
}

} // namespace smart_home