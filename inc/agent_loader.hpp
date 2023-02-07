#ifndef AGENT_LOADER_HPP
#define AGENT_LOADER_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <fstream>

#include "events_publisher.hpp"
#include "agent_interface.hpp"
#include "threads_concurrent_hash_table.hpp"

namespace smart_home 
{
class AgentLoader 
{
public:
    AgentLoader(std::ifstream& a_stream);
    AgentLoader(AgentLoader const& a_other) = default;
    AgentLoader& operator=(AgentLoader const& a_other) = default;
    ~AgentLoader() = default;

    threads::ConcurrentHashTable<std::string, std::shared_ptr<IAgent>> Load(std::shared_ptr<EventsPublisher> a_eventStation); 

private:
    std::ifstream& m_stream;
};
}//smart_home

#endif /* AGENT_LOADER_HPP */