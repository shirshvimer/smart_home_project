#ifndef EVENT_HPP
#define EVENT_HPP

#include <chrono> //system_clock
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>

#include "location.hpp"
#include "save_data_interface.hpp"

namespace smart_home 
{
struct Event 
{
public:
    // std::ostream& Print(std::ostream &a_out) const;
    void Print(InterfaceSaveData& a_logger) const;

    std::string timestamp;
    std::string eType;
    Location location;
    std::vector<std::string> payload;
};
}//smart_home

#include "inl/event.hxx"

#endif /* EVENT_HPP */