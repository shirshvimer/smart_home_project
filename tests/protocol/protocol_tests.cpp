#include <vector>       // vector 
#include <string>       // string 
#include <chrono>       // system_clock 
#include <iostream>		// cout 

#include "protocol.hpp" 

using namespace smart_home; 

static void TetsPrintStringsInProtocol(void); 

int main() 
{ 
    TetsPrintStringsInProtocol(); 
    

    return 0; 
} 

static void TetsPrintStringsInProtocol(void) 
{ 
	Protocol testProtocol; 
	std::string const testDeviceID {"temprature sensor"}; 
	std::chrono::time_point<std::chrono::system_clock> const testNow = std::chrono::system_clock::now(); 
	std::vector<std::string> const testPayload {("hot"), ("cold")}; 
	std::vector<unsigned char> testSendBuffer; 
	std::vector<std::string> testReceivedBuffer; 

	testSendBuffer = testProtocol.Pack(testDeviceID, testNow, testPayload); 

	for (auto const& element : testSendBuffer) { 
		std::cout << element << " "; 
	} 
	std::cout << std::endl; 

	std::cout << "Send buffer size: " << testSendBuffer.size() << std::endl; 

	std::cout << "After packed:" << "\n"; 

	testReceivedBuffer = testProtocol.UnPack(testSendBuffer); 

	for (auto const& element : testReceivedBuffer) { 
		std::cout << element << " " << std::endl; 
	} 
	std::cout << std::endl; 
	
	return; 
} 

/* 
template<typename C> 
static void packBufferToBytes (C const& a_container, std::vector<unsigned char>& a_buffer) 
{ 
    size_t sizeOfElementInContainer = sizeof(typename C::value_type); 
    for(auto& element : a_container) { 
        unsigned char const* eight_bytes_ptr = reinterpret_cast<unsigned char const*>(&element); 
        for(size_t i = 0; i < sizeOfElementInContainer ; ++i) { 
            a_buffer.push_back(eight_bytes_ptr[i]); 
        } 
    } 
} */ 