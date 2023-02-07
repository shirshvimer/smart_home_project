#ifndef LOCATION_HXX
#define LOCATION_HXX

#include <string>
#include "location.hpp"

namespace smart_home 
{
inline Location::Location(std::string const& a_room, std::string const& a_floor) 
: room(a_room)
, floor(a_floor) 
{
}

inline bool Location::operator==(Location const& a_other) const
{
    return room == a_other.room && floor == a_other.floor;
}

}//smart_home

#endif /* LOCATION_HXX */