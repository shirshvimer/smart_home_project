#include "sensor_interface.hpp"
#include "sensor_temperature.hpp"
#include "sensor_fire_detector.hpp"
#include "sensor_badge.hpp"
#include "protocol.hpp"

#include <thread>

int main ()
{
    using namespace smart_home;

    Protocol protocol;
    TemperatureSensor tempSens{protocol, "[temp-1-a]", "127.0.0.1", 8080};
    FireDetectorSensor fireSens{protocol, "[fire-1-a]", "127.0.0.1", 8080};
    BadgeSensor badgeSens{protocol, "[badge-1-a]", "127.0.0.1", 8080};

    std::thread t1{[&](){
        tempSens.Run();
        }};

    std::thread t2{[&](){
        fireSens.Run();
        }};

    std::thread t3{[&](){
        badgeSens.Run();
        }};

    badgeSens.SubmitEnteranceRequest("12", "ABDE570");
    badgeSens.SubmitEnteranceRequest("17", "X2XXO73");
    badgeSens.SubmitEnteranceRequest("25", "Y3RTF45");

    t1.join();
    t2.join();
    t3.join();

    return 0;
}