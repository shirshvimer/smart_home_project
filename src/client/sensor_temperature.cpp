#include "sensor_temperature.hpp"

#include <cstdlib>
#include <ctime> 
#include <vector>

namespace smart_home 
{

namespace details
{
const int lowRange = 0;
const int upRange = 100;
}

TemperatureSensor::TemperatureSensor(Protocol const& a_protocol, std::string const& a_deviceID, std::string const& a_ip, size_t a_port)
: BaseSensor(a_protocol, a_deviceID, a_ip, a_port)
, m_temperature(20)
{
}

void TemperatureSensor::Run()
{
#ifdef TEST_SPRINKLER
    m_temperature = 70;
    std::vector<unsigned char> data = m_protocol.Pack(m_deviceID, std::chrono::system_clock::now(), std::vector<std::string> {std::to_string(m_temperature)});
    m_socket.Send(data);

#else 
    while(true) {
        srand(time(0));
        m_temperature = details::lowRange + (rand() % details::upRange);
        std::vector<unsigned char> data = m_protocol.Pack(m_deviceID, std::chrono::system_clock::now(), std::vector<std::string> {std::to_string(m_temperature)});
        
        
        //std::cout << "temp sensor\n";

        m_socket.Send(data);
        sleep(1);
    }
#endif
}

}//smart_home