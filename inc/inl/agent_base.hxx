#ifndef AGENT_BASE_HXX
#define AGENT_BASE_HXX

#include "agent_base.hpp"

namespace smart_home 
{

inline AgentBase::AgentBase(std::string const& a_id, Location const& a_location, std::string const& a_log, std::string const& a_config)
: m_id(a_id)
, m_location(a_location)
, m_log(a_log) 
, m_config(a_config)
// , m_fb()
// , m_logStream(m_fb.open(a_log, std::ios::app))
{
}

inline std::string AgentBase::ID() const 
{ 
    return m_id; 
} 

inline void AgentBase::Singup(std::shared_ptr<EventsPublisher> a_eventsPublisher)
{
    
}

}//smart_home

#endif /* AGENT_BASE_HXX */