#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <vector>       // vector 
#include <string>       // string 
#include <chrono>       //system_clock 

namespace smart_home 
{
class Protocol 
{
public:
    Protocol() = default;
    Protocol(Protocol const& a_other) = default;
    Protocol& operator=(Protocol const& a_other) = default;
    ~Protocol() = default;

    std::vector<unsigned char> Pack(std::string const& a_deviceID, std::chrono::system_clock::time_point const& a_timeStamp, std::vector<std::string> const& a_payload) const; 
    size_t UnPackSize(std::vector<unsigned char>& a_packedBuffer) const; 
    std::vector<std::string> UnPack(std::vector<unsigned char>& a_packedBuffer) const; 

};
}//smart_home

#endif /* PROTOCOL_HPP */ 