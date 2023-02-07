#include "sensor_fire_detector.hpp"

#include <cstdlib>
#include <ctime> 
#include <vector>

namespace smart_home 
{

FireDetectorSensor::FireDetectorSensor(Protocol const& a_protocol, std::string const& a_deviceID, std::string const& a_ip, size_t a_port)
: BaseSensor(a_protocol, a_deviceID, a_ip, a_port)
, m_signal()
{
}

void FireDetectorSensor::Run()
{
    
    while(true) {
        srand(time(0)); 
        int randomNum = 0 + (rand() % 10);
        if( (randomNum % 4) == 0) {
            m_signal = "SIG_NO_FIRE";
        }
        else {
            m_signal = "SIG_FIRE";
        }
         
        std::vector<unsigned char> data = m_protocol.Pack(m_deviceID,  std::chrono::system_clock::now(), std::vector<std::string> {m_signal});
        
        //std::cout << "fire sensor\n";
        m_socket.Send(data);
        sleep(1);
    }
}

}//smart_home