#ifndef SENSOR_TEMPERATURE_HPP
#define SENSOR_TEMPERATURE_HPP

#include "sensor_base.hpp"

namespace smart_home 
{

class TemperatureSensor : public BaseSensor
{
public:
    TemperatureSensor(Protocol const& a_protocol, std::string const& a_deviceID, std::string const& a_ip, size_t a_port);

    virtual void Run() override;

private:
    int m_temperature;

};



}//smart_home


#endif /* SENSOR_TEMPERATURE_HPP */
