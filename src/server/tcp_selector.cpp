#include "tcp_selector.hpp"

namespace net {

Selector::Selector(TCPServerSocket& a_server, std::unique_ptr<Handler>& a_handler, std::unique_ptr<Acceptor>& a_acceptor)
: m_server(a_server)
, m_handler(a_handler)
, m_acceptor(a_acceptor)
, m_isTerminate(false)
{
    FD_ZERO(&m_master);
    FD_ZERO(&m_active);
}

void Selector::Run()
{
    using ClientPtr = std::shared_ptr<TCPClientSocket>;
    std::vector<ClientPtr> clients;
    
    Add(m_server);

    while(!m_isTerminate) {
        int activity = Wait();
        if(activity > 0) {
            
            if(IsActive(m_server)) {
                ClientPtr c = m_server.Accept();
                Add(*c);
                
                clients.push_back( std::move(c) );
                --activity;
            }

            if(activity > 0) {
                typename std::vector<ClientPtr>::iterator it = clients.begin();
                typename std::vector<ClientPtr>::iterator end = clients.end();
                
                while(it != end && activity > 0) {
                    if(IsActive(**it)) {
                        try {
                            m_handler->HandlerIncoming(*it);
                        }
                        catch(...) {
                            Remove(**it);
                            it = clients.erase(it);
                            --activity;
                            continue;
                        }
                        --activity;
                    }
                    it++;
                }
            }
        }
    }
}

void Selector::Shutdown()
{
    m_isTerminate = true;
}

void Selector::Add(TCPClientSocket const& a_socket)
{
    FD_SET(a_socket.Socket(), &m_master);
}

void Selector::Add(TCPServerSocket const& a_socket)
{
    FD_SET(a_socket.Socket(), &m_master);
}

void Selector::Remove(TCPClientSocket const& a_socket)
{
    FD_CLR(a_socket.Socket(), &m_master);
}

void Selector::Remove(TCPServerSocket const& a_socket)
{
    FD_CLR(a_socket.Socket(), &m_master);
}

int Selector::Wait()
{
    m_active = m_master;
    int numOfActivity = select(1024, &m_active, NULL, NULL, NULL);

    if ((numOfActivity < 0) && (errno!=EINTR))
    {
        throw SelectorException("select", "select failed"); 
    }

    return numOfActivity;
}

bool Selector::IsActive(TCPClientSocket const& a_socket) const
{
    return FD_ISSET(a_socket.Socket(), &m_active);
}

bool Selector::IsActive(TCPServerSocket const& a_socket) const
{
    return FD_ISSET(a_socket.Socket(), &m_active);
}

}//net