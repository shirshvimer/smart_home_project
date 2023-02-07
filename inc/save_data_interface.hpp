#ifndef SAVE_DATA_INTERFACE_HPP
#define SAVE_DATA_INTERFACE_HPP

#include <vector>
#include <string>

namespace smart_home
{

class InterfaceSaveData
{
public:
    ~InterfaceSaveData() = default;

    virtual void Save(std::vector<std::pair<std::string, std::string>> const& a_data) = 0;

protected:
    InterfaceSaveData() = default;
    InterfaceSaveData(InterfaceSaveData const& a_other) = default;
    InterfaceSaveData& operator=(InterfaceSaveData const& a_other) = default;

};



} // namespace smart_home




#endif /* SAVE_DATA_INTERFACE_HPP */