#ifndef SENSOR_FIRE_DETECTOR_HPP
#define SENSOR_FIRE_DETECTOR_HPP

#include "sensor_base.hpp"

namespace smart_home 
{

class FireDetectorSensor : public BaseSensor
{
public:
    FireDetectorSensor(Protocol const& a_protocol, std::string const& a_deviceID, std::string const& a_ip, size_t a_port);

    virtual void Run() override;

private:
    std::string m_signal;
};



}//smart_home


#endif /* SENSOR_FIRE_DETECTOR_HPP */
