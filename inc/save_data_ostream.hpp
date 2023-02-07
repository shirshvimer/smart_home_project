#ifndef SAVE_DATA_OSTREAM_HPP
#define SAVE_DATA_OSTREAM_HPP

#include <vector>
#include <string>
#include <ostream>

#include "save_data_base.hpp"

namespace smart_home
{

class SaveDataOstream : public BaseSaveData
{
public:
    SaveDataOstream(std::ostream& a_stream);
    SaveDataOstream(SaveDataOstream const& a_other) = delete;
    SaveDataOstream& operator=(SaveDataOstream const& a_other) = delete;
    ~SaveDataOstream() = default;

    virtual void Save(std::vector<std::pair<std::string, std::string>> const& a_data) override;
    
private:
    std::ostream& m_stream;

};

} // namespace smart_home

#endif /* SAVE_DATA_OSTREAM_HPP */