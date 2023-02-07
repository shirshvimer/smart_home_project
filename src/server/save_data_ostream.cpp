#include "save_data_ostream.hpp"
#include "iostream"

namespace smart_home
{

SaveDataOstream::SaveDataOstream(std::ostream& a_stream)
: m_stream(a_stream)
{    
}

void SaveDataOstream::Save(std::vector<std::pair<std::string, std::string>> const& a_data)
{
    std::lock_guard<std::mutex> guard {m_mtx};
    for(auto const& e : a_data) {
        m_stream << e.first << ": ";
        m_stream << e.second ;
        m_stream << std::endl;
    }
    m_stream << std::endl;
}

} // namespace smart_home