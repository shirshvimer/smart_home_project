#include "server_app.hpp"
#include "tcp_event_handler.hpp"

#include <iostream>
namespace smart_home 
{

ServerApp::ServerApp(std::string const& a_ip, size_t a_port, std::ifstream& a_configStream, InterfaceSaveData& a_logStream, size_t a_numOfThreads)
: m_server(a_ip.c_str(), a_port)
, m_handler(new net::EventHandler{a_configStream, a_logStream, a_numOfThreads})
, m_acceptor(new net::DefaultAcceptor{})
, m_selector(m_server, m_handler, m_acceptor)
{
}

void ServerApp::Run()
{
    m_selector.Run();
}

void ServerApp::Shutdown() 
{
    m_selector.Shutdown();
} 

}//smart_home