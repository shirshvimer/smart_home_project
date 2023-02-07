#ifndef SENSOR_BADGE_HPP
#define SENSOR_BADGE_HPP

#include <memory>

#include "sensor_base.hpp"
#include "threads_blocking_queue.hpp"

namespace smart_home 
{

class BadgeSensor : public BaseSensor
{
public:
    BadgeSensor(Protocol const& a_protocol, std::string const& a_deviceID, std::string const& a_ip, size_t a_port);

    virtual void Run() override;
    void SubmitEnteranceRequest(std::string const& a_employeeID, std::string const& a_badgeID);

private:
    struct EnterRequestData {
        EnterRequestData(std::string const& a_employeeID, std::string const& a_secureSig) : m_employeeID(a_employeeID), m_secureSig(a_secureSig) {};
        std::string m_employeeID;
        std::string m_secureSig;
    };

private:
    threads::BlockingQueue<std::unique_ptr<EnterRequestData>> m_blockingQueue;
};



}//smart_home


#endif /* SENSOR_BADGE_HPP */
