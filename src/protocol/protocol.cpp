#include <cstring>      //memcpy
#include <arpa/inet.h>  //htonl
#include <iostream>		// cout 

#include "protocol.hpp" 

namespace smart_home { 

static void packSizeOfString(size_t const& a_element, std::vector<unsigned char>& a_buffer) 
{ 
    size_t sizeOfElement = sizeof(size_t); 
    unsigned char const* eightBytesPointer = reinterpret_cast<unsigned char const*>(&a_element); 
    for(size_t i = 0; i < sizeOfElement; ++i) { 
        a_buffer.push_back(eightBytesPointer[i]); 
    } 
} 

static void packStringToBuffer(std::string const& a_string, std::vector<unsigned char>& a_buffer) 
{ 
    size_t sizeOfElementInContainer = sizeof(std::string::value_type); 
    for(auto& element : a_string) { 
        unsigned char const* eightBytesPointer = reinterpret_cast<unsigned char const*>(&element); 
        for(size_t i = 0; i < sizeOfElementInContainer ; ++i) { 
            a_buffer.push_back(eightBytesPointer[i]); 
        } 
    } 
} 

static std::string timePointAsString(std::chrono::system_clock::time_point const& a_timePoint) { 
    std::time_t systemTime = std::chrono::system_clock::to_time_t(a_timePoint); 
    std::string timeString = std::ctime(&systemTime); 
    timeString.resize(timeString.size()-1); 
    
    return timeString; 
} 


std::vector<unsigned char> Protocol::Pack(std::string const& a_deviceID, std::chrono::system_clock::time_point const& a_timeStamp, std::vector<std::string> const& a_payload) const 
{ 
    std::vector<unsigned char> sendBuffer; 
    std::string timeString; 
    size_t dataSizeDeviceID, dataSizeTimeStamp, dataSizeVector, sizeOfStringsInVector = 0, dataSizeBuffer; 
    std::vector<size_t> dataSizeString; 

    dataSizeDeviceID = a_deviceID.size(); 
    
    //auto current_time = std::chrono::system_clock::now(); 
    timeString = timePointAsString(a_timeStamp); 
    dataSizeTimeStamp = timeString.size(); 

    dataSizeVector = a_payload.size(); 
    dataSizeString.reserve(a_payload.size()); 
    
    for (size_t i = 0; i < dataSizeVector; ++i) { 
        dataSizeString[i] = a_payload[i].size(); 
        sizeOfStringsInVector += dataSizeString[i]; 
    } 

    dataSizeBuffer = 24 + (dataSizeVector * 8) + dataSizeDeviceID + dataSizeTimeStamp + sizeOfStringsInVector; 
    
    packSizeOfString(dataSizeBuffer, sendBuffer); 
    packSizeOfString(dataSizeDeviceID, sendBuffer); 
    packSizeOfString(dataSizeTimeStamp, sendBuffer); 
    packSizeOfString(dataSizeVector, sendBuffer); 
    
    for (size_t i = 0; i < dataSizeVector; ++i) { 
        //dataSizeString[i] = a_payload[i].size(); 
        packSizeOfString(dataSizeString[i], sendBuffer); 
    } 

    packStringToBuffer(a_deviceID, sendBuffer); 
    
    packStringToBuffer(timeString, sendBuffer); 
    
    for (size_t i = 0; i < dataSizeVector; ++i) { 
        packStringToBuffer(a_payload[i], sendBuffer); 
    } 

    return sendBuffer; 
} 

size_t Protocol::UnPackSize(std::vector<unsigned char>& a_packedBuffer) const
{ 
    size_t finalsize; 
    size_t sizeOfElement = sizeof(size_t);

    memcpy(&finalsize, reinterpret_cast<size_t*>(&a_packedBuffer[0]), sizeOfElement); 
    
    return finalsize;
} 

static size_t unpackSizeOfString(std::vector<unsigned char>& a_packedBuffer, size_t& a_startIndexInBuffer) 
{ 
    size_t finalsize; 
    size_t sizeOfElement = sizeof(size_t); 

    memcpy(&finalsize, reinterpret_cast<size_t*>(&a_packedBuffer[a_startIndexInBuffer]), sizeOfElement); 
    a_startIndexInBuffer += sizeOfElement; 

    return finalsize; 
} 

std::vector<std::string> Protocol::UnPack(std::vector<unsigned char>& a_packedBuffer) const 
{ 
    //std::vector<std::string> unpackedDeviceData; 
    size_t unsignedCharSize = sizeof(unsigned char); 
    size_t currentIndexInPackedBuffer = 0; 
    size_t dataSizeDeviceID, dataSizeTimeStamp, dataSizeVector, sizeOfStringInBuffer; 
    std::vector<size_t> dataSizeString; 

    /*********************************************for tests*********************************************/
    /* size_t dataSizeBuffer = unpackSizeOfString(a_packedBuffer, currentIndexInPackedBuffer); 
    (void) dataSizeBuffer; 
    //currentIndexInPackedBuffer = 8;  */  

    dataSizeDeviceID = unpackSizeOfString(a_packedBuffer, currentIndexInPackedBuffer); 
    dataSizeTimeStamp = unpackSizeOfString(a_packedBuffer, currentIndexInPackedBuffer); 
    dataSizeVector = unpackSizeOfString(a_packedBuffer, currentIndexInPackedBuffer);
    
    //std::cout << "size dataSizeDeviceID in protocol : " << dataSizeDeviceID << '\n';
    //std::cout << "size dataSizeTimeStamp in protocol : " << dataSizeTimeStamp << '\n';
    //std::cout << "size dataSizeVector in protocol : " << dataSizeVector << '\n';
    
    sizeOfStringInBuffer = (2 + dataSizeVector); 
    std::vector<std::string> unpackedDeviceData (sizeOfStringInBuffer, {""});  

    dataSizeString.reserve(dataSizeVector); 

    for (size_t i = 0; i < dataSizeVector; ++i) { 
        dataSizeString[i] = unpackSizeOfString(a_packedBuffer, currentIndexInPackedBuffer); 
    }  

    for(size_t j = 0; j < dataSizeDeviceID; ++j) { 
        char elememt; 
        memcpy(&elememt, reinterpret_cast<char*>(&a_packedBuffer[currentIndexInPackedBuffer + (j * unsignedCharSize)]), unsignedCharSize); 
        unpackedDeviceData[0].push_back(elememt); 
    } 
    currentIndexInPackedBuffer += dataSizeDeviceID; 

    for(size_t j = 0; j < dataSizeTimeStamp; ++j) { 
        char elememt; 
        memcpy(&elememt, reinterpret_cast<char*>(&a_packedBuffer[currentIndexInPackedBuffer + (j * unsignedCharSize)]), unsignedCharSize); 
        unpackedDeviceData[1].push_back(elememt); 
    } 
    currentIndexInPackedBuffer += dataSizeTimeStamp; 

    for (size_t i = 0; i < dataSizeVector; ++i) { 
        for(size_t j = 0; j < dataSizeString[i]; ++j) { 
            char elememt; 
            memcpy(&elememt, reinterpret_cast<char*>(&a_packedBuffer[currentIndexInPackedBuffer + (j * unsignedCharSize)]), unsignedCharSize); 
            unpackedDeviceData[(2 + i)].push_back(elememt); 
        } 
        currentIndexInPackedBuffer += dataSizeString[i]; 
    } 
    
    return unpackedDeviceData; 
} 

} //smart_home 