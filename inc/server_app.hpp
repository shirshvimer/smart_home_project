#ifndef SERVER_APP_HPP
#define SERVER_APP_HPP

#include <chrono> //system_clock
#include <string>
#include <vector>
#include <memory>

#include "tcp_selector.hpp"
#include "tcp_server_socket.hpp"
#include "tcp_acceptor.hpp"
#include "save_data_interface.hpp"

namespace smart_home 
{
class ServerApp 
{
public:
    ServerApp(std::string const& a_ip, size_t a_port, std::ifstream& a_configStream, InterfaceSaveData& a_logStream, size_t a_numOfThreads);
    ServerApp(ServerApp const& a_other) = delete;
    ServerApp& operator=(ServerApp const& a_other) = delete;
    ~ServerApp() = default;

    void Run();
    void Shutdown();

private:
    net::Selector initSelector();

private:
    net::TCPServerSocket m_server;
    std::unique_ptr<net::Handler> m_handler;
    std::unique_ptr<net::Acceptor> m_acceptor;
    net::Selector m_selector;
};
}//smart_home

#endif /* SERVER_APP_HPP */