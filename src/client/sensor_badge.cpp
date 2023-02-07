#include "sensor_badge.hpp"

#include <cstdlib>
#include <ctime> 
#include <vector>

namespace smart_home 
{

BadgeSensor::BadgeSensor(Protocol const& a_protocol, std::string const& a_deviceID, std::string const& a_ip, size_t a_port)
: BaseSensor(a_protocol, a_deviceID, a_ip, a_port)
, m_blockingQueue()
{
}

void BadgeSensor::Run()
{
    while(true) {
        std::unique_ptr<EnterRequestData> payload;
        m_blockingQueue.DeQueue(payload);
         
        std::vector<unsigned char> data = m_protocol.Pack(m_deviceID,  std::chrono::system_clock::now(), std::vector<std::string> {payload->m_employeeID, payload->m_secureSig});
        
        //std::cout << "badge sensor\n";
        m_socket.Send(data);
        sleep(1);
    }
}

void BadgeSensor::SubmitEnteranceRequest(std::string const& a_employeeID, std::string const& a_secureSig)
{
    m_blockingQueue.EnQueue(std::make_unique<EnterRequestData>(a_employeeID, a_secureSig));
}

}//smart_home