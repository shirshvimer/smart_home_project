#include <fstream>
#include <thread>

#include "mu_test.h"

#include "server_app.hpp"
#include "sensor_interface.hpp"
#include "sensor_temperature.hpp"
#include "protocol.hpp"

BEGIN_TEST(test)
    using namespace smart_home;

    std::ifstream config("config.txt");
    
    size_t numOfThreads = 3;
    std::ofstream log("log.txt");

    ServerApp serverApp{"127.0.0.1", 8080, config, log, numOfThreads};

    std::thread runServer{[&](){
        serverApp.Run();
        }};
 
    Protocol protocol;
    TemperatureSensor tempSens{protocol, "[temp-1-a]", "127.0.0.1", 8080};

    std::thread runSensor{[&](){
        tempSens.Run();
        }};

    runSensor.join();

    sleep(3.5);

    std::ifstream logStream("log.txt");
    std::string controller;

    while(logStream.is_open() && !logStream.eof()) {
        logStream >> controller;

        if(controller == "CONTROLLER_SPRINKLER_ON") {
            ASSERT_PASS();
            break;
        }
    }
    
    std::thread shutdownServer{[&](){
        serverApp.Shutdown();
        }};
    
    shutdownServer.join();

    std::thread wakeUpServer{[&](){
        tempSens.Run();
        }};

    wakeUpServer.join();
    
    runServer.join();
END_TEST


BEGIN_SUITE(Its what you learn after you know it all that counts)
	TEST(test)
END_SUITE