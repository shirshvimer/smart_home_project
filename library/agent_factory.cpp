#include "agent_factory.hpp"

namespace smart_home
{

static void initMap(std::unordered_map<std::string, std::unique_ptr<IAgentGenerator>>& a_map)
{
    a_map.insert(std::make_pair("sen_temp", std::make_unique<TempSensGenerator>()));
    a_map.insert(std::make_pair("con_ac", std::make_unique<ACConGenerator>()));
    a_map.insert(std::make_pair("sen_fire_detector", std::make_unique<FireDetectorSenGenerator>()));
    a_map.insert(std::make_pair("con_sprinkler", std::make_unique<SprinklerConGenerator>()));
    a_map.insert(std::make_pair("sen_badge", std::make_unique<BadgeSenGenerator>()));
    a_map.insert(std::make_pair("con_door", std::make_unique<DoorConGenerator>()));
}
    
AgentFactory::AgentFactory(std::shared_ptr<EventsPublisher> a_eventPublisher)
: m_eventStation(a_eventPublisher)
, m_lookupMap()
{
    initMap(m_lookupMap);
}

std::shared_ptr<IAgent> AgentFactory::Get(std::string const& a_type, std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config)
{
    return m_lookupMap.at(a_type)->GeneratePtr(a_id, a_loction, a_log, a_config, m_eventStation);
}

} // namespace smart_home
