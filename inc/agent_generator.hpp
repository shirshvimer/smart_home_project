#ifndef AGENT_GENERATOR_HPP
#define AGENT_GENERATOR_HPP

#include <memory>

#include "agent_interface.hpp"

namespace smart_home
{
    
class IAgentGenerator
{
public:
    IAgentGenerator() = default;
    virtual ~IAgentGenerator() = default;
    virtual std::shared_ptr<IAgent> GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher) = 0;
};

class TempSensGenerator : public IAgentGenerator
{
public:
    using IAgentGenerator::IAgentGenerator;
    std::shared_ptr<IAgent> GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher) override;
};

class ACConGenerator : public IAgentGenerator
{
public:
    using IAgentGenerator::IAgentGenerator;
    std::shared_ptr<IAgent> GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher) override;
};

class FireDetectorSenGenerator : public IAgentGenerator
{
public:
    using IAgentGenerator::IAgentGenerator;
    std::shared_ptr<IAgent> GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher) override;
};

class SprinklerConGenerator : public IAgentGenerator
{
public:
    using IAgentGenerator::IAgentGenerator;
    std::shared_ptr<IAgent> GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher) override;
};

class BadgeSenGenerator : public IAgentGenerator
{
public:
    using IAgentGenerator::IAgentGenerator;
    std::shared_ptr<IAgent> GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher) override;
};

class DoorConGenerator : public IAgentGenerator
{
public:
    using IAgentGenerator::IAgentGenerator;
    std::shared_ptr<IAgent> GeneratePtr(std::string const& a_id, Location const& a_loction, std::string const& a_log, std::string const& a_config, std::shared_ptr<EventsPublisher> a_eventPublisher) override;
};


} // namespace smart_home


#endif // AGENT_GENERATOR_HPP