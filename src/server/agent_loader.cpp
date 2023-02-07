#include <string>

#include "agent_loader.hpp"
#include "agent_factory.hpp"

namespace smart_home
{

AgentLoader::AgentLoader(std::ifstream& a_stream)
: m_stream(a_stream)
{
}

static std::unordered_map<std::string, std::string> initConfigMap()
{
    std::unordered_map<std::string, std::string> configMap{ {"id", ""},
                                                            {"type", ""},
                                                            {"room", ""},
                                                            {"floor", ""},
                                                            {"log", ""},
                                                            {"config", ""}};

    return configMap;
}
    
threads::ConcurrentHashTable<std::string, std::shared_ptr<IAgent>> AgentLoader::Load(std::shared_ptr<EventsPublisher> a_eventPublisher)
{
    threads::ConcurrentHashTable<std::string, std::shared_ptr<IAgent>> agents;
    AgentFactory factory{a_eventPublisher};
    
    std::unordered_map<std::string, std::string> configMap = initConfigMap();
    
    if(!m_stream.is_open()){
        throw std::runtime_error("file doesn't exist");
    }

    std::string key = "", val = "", trash = "";
    m_stream >> key;

    while(!m_stream.eof()) {
        
        configMap.at("id") = key;
        
        m_stream >> key;
        
        while(key[0] != '[' && !m_stream.eof()) {
            m_stream >> trash >> val;
            configMap.at(key) = val;

            m_stream >> key;
        }

        Location location{configMap.at("room"), configMap.at("floor")};
        
        std::shared_ptr<IAgent> agent = factory.Get(configMap.at("type"), configMap.at("id"), location, configMap.at("log"), configMap.at("config"));
        agents.Insert(configMap.at("id"), agent);

        configMap.at("log") = "";
        configMap.at("config") = "";
    }
    
    return agents;
}

} // namespace smart_home
