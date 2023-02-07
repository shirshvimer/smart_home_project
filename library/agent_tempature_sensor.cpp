#include "agent_tempature_sensor.hpp"

namespace smart_home
{

TempatureSensorAgent::TempatureSensorAgent(std::string const& a_id, Location const& a_location, std::string const& a_log, std::string const& a_config)
: AgentBase::AgentBase(a_id, a_location, a_log, a_config)
{}
    
Event TempatureSensorAgent::Act(std::vector<std::string> const& a_data, iagent::EventPtr a_eventsPublisher) const
{
    Event event;
    event.eType = "TEMP_LEVEL";
    event.location = m_location;
    event.timestamp = a_data[1];
    size_t size = a_data.size();
    for (size_t i = 2; i < size; i++) {
        event.payload.push_back(a_data[i]);
    }
    
    return event;
}

} // namespace smart_home
