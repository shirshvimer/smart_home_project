#ifndef SAVE_DATA_DB_HPP
#define SAVE_DATA_DB_HPP

#include <unordered_map>
#include <string>
#include <memory>

#include "save_data_base.hpp"
#include "mysql_connection.h"

namespace smart_home
{

class SaveDataDB : public BaseSaveData
{
public:
    SaveDataDB(sql::Connection* a_dbConnection, std::string const& a_tableName);
    SaveDataDB(SaveDataDB const& a_other) = delete;
    SaveDataDB& operator=(SaveDataDB const& a_other) = delete;
    ~SaveDataDB() = default;

    virtual void Save(std::vector<std::pair<std::string, std::string>> const& a_data) override;
    
private:
    sql::Connection* m_dbConnection;
    std::string m_tableName;
};

} // namespace smart_home

#endif /* SAVE_DATA_DB_HPP */