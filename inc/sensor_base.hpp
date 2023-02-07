#ifndef SENSOR_BASE_HPP
#define SENSOR_BASE_HPP

#include <string>

#include "sensor_interface.hpp"
#include "protocol.hpp"
#include "tcp_client_socket.hpp"

namespace smart_home
{
class BaseSensor : public ISensor
{
public:
    virtual ~BaseSensor() = default;

    virtual void Run() = 0;

protected:
    BaseSensor(Protocol const& a_protocol, std::string const& a_deviceID, std::string const& a_ip, size_t a_port);
    BaseSensor(BaseSensor const& a_other) = default;
    BaseSensor& operator=(BaseSensor const& a_other) = default;

protected:    
    Protocol m_protocol;
    std::string m_deviceID;
    net::TCPClientSocket m_socket;
};

}//smart_home

#endif /* SENSOR_BASE_HPP */