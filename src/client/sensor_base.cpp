#include "sensor_base.hpp"

namespace smart_home 
{

BaseSensor::BaseSensor(Protocol const& a_protocol, std::string const& a_deviceID, std::string const& a_ip, size_t a_port)
: m_protocol(a_protocol)
, m_deviceID(a_deviceID)
, m_socket(a_ip.c_str(), a_port)
{
}


}//smart_home   