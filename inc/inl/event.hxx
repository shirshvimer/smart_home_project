#ifndef EVENT_HXX
#define EVENT_HXX

#include <iomanip>

#include "event.hpp"

namespace smart_home 
{
inline void Event::Print(InterfaceSaveData& a_logger) const
{ 
    std::vector<std::pair<std::string, std::string>> data { {"Time", timestamp}, {"Type", eType}, {"Floor", location.floor}, {"Room", location.room}};

    std::string payloadStr{""};

    for(auto const& str: payload) {
        payloadStr += str;
        payloadStr += " ";
    }
    
    data.push_back( {"Payload", payloadStr});
    a_logger.Save(data);

    return;
}

}//smart_home

#endif /* EVENT_HXX */