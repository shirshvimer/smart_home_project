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
    
    size_t numOfThreads = 4;

    std::ofstream log("log.txt");
    SaveDataOstream saveStream{log};
    
    ServerApp serverApp{"127.0.0.1", 8080, stream, saveStream, numOfThreads};
    
    serverApp.Run();

    return 0;
}