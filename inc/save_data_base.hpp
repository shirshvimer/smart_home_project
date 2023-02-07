#ifndef SAVE_DATA_BASE_HPP
#define SAVE_DATA_BASE_HPP

#include <mutex>
#include "save_data_interface.hpp"

namespace smart_home
{

class BaseSaveData :public InterfaceSaveData
{
public:
    ~BaseSaveData() = default;

    virtual void Save(std::vector<std::pair<std::string, std::string>> const& a_data) = 0;

protected:
    BaseSaveData() = default;
    BaseSaveData(BaseSaveData const& a_other) = default;
    BaseSaveData& operator=(BaseSaveData const& a_other) = default;

protected:
    std::mutex m_mtx;
};



} // namespace smart_home




#endif /* SAVE_DATA_BASE_HPP */