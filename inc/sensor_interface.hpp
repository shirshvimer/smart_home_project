#ifndef SENSOR_INTERFACE_HPP
#define SENSOR_INTERFACE_HPP

#include <string>

#include "protocol.hpp"
#include "tcp_client_socket.hpp"

namespace smart_home 
{
class ISensor 
{
public:
    virtual ~ISensor() = default;

    virtual void Run() = 0;

protected:
    ISensor() = default;
    ISensor(ISensor const& a_other) = default;
    ISensor& operator=(ISensor const& a_other) = default;
};

}//smart_home

#endif /* SENSOR_INTERFACE_HPP */
