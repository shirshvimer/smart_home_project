#include "agent_generator.hpp"

#include "agent_tempature_sensor.hpp"
#include "agent_aircondition.hpp"
#include "agent_fire_detector_sensor.hpp"
#include "agent_sprinkler.hpp"
#include "agent_badge_sensor.hpp"
#include "agent_door.hpp"

namespace smart_home
{
    
std::shared_ptr<IAgent> TempSensGenerator::GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher)
{
    std::shared_ptr<IAgent> ptr = std::make_shared<TempatureSensorAgent>(a_id, a_loction, a_log, a_config);
    ptr->Singup(a_eventPublisher);
    return ptr;
}

std::shared_ptr<IAgent> ACConGenerator::GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher)
{
    std::shared_ptr<IAgent> ptr = std::make_shared<ACAgent>(a_id, a_loction, a_log, a_config);
    ptr->Singup(a_eventPublisher);
    return ptr;
}

std::shared_ptr<IAgent> FireDetectorSenGenerator::GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher)
{
    std::shared_ptr<IAgent> ptr = std::make_shared<FireDetectorSensorAgent>(a_id, a_loction, a_log, a_config);
    ptr->Singup(a_eventPublisher);
    return ptr;
}

std::shared_ptr<IAgent> SprinklerConGenerator::GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher)
{
    std::shared_ptr<IAgent> ptr = std::make_shared<SprinklerAgent>(a_id, a_loction, a_log, a_config);
    ptr->Singup(a_eventPublisher);
    return ptr;
}

std::shared_ptr<IAgent> BadgeSenGenerator::GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher)
{
    std::shared_ptr<IAgent> ptr = std::make_shared<BadgeSensorAgent>(a_id, a_loction, a_log, a_config);
    ptr->Singup(a_eventPublisher);
    return ptr;
}

std::shared_ptr<IAgent> DoorConGenerator::GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher)
{
    std::shared_ptr<IAgent> ptr = std::make_shared<DoorAgent>(a_id, a_loction, a_log, a_config);
    ptr->Singup(a_eventPublisher);
    return ptr;
}

} // namespace smart_home