#include <fstream>
#include "server_app.hpp"
#include "save_data_interface.hpp"
#include "save_data_ostream.hpp"
#include "save_data_db.hpp"
#include "mysql_connection.h"
#include <cppconn/driver.h>

int main() 
{
    using namespace smart_home;
    
    std::ifstream stream("config.txt");
    
    size_t numOfThreads = 3;

    sql::Driver *driver;
    sql::Connection* con;
    driver = get_driver_instance();
    con = driver->connect("localhost", "matanl2208", "cgyd78wk"); // Insert your username and password
    con->setSchema("smart_home_log");
    SaveDataDB saveStreamDB{con, "events"};
    
    ServerApp serverApp{"127.0.0.1", 8080, stream, saveStreamDB, numOfThreads};
    
    serverApp.Run();

    return 0;
}