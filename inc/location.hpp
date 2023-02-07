#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

namespace smart_home 
{
struct Location 
{
public:
    Location() = default;
    Location(std::string const& a_room, std::string const& a_floor);

    bool operator==(Location const& a_other) const;

    std::string room;
    std::string floor;
};
}//smart_home

#include "location.hxx"

#endif /* LOCATION_HPP */