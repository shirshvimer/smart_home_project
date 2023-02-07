#include "save_data_db.hpp"

#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace smart_home
{

SaveDataDB::SaveDataDB(sql::Connection* a_dbConnection, std::string const& a_tableName)
: m_dbConnection(a_dbConnection)
, m_tableName(a_tableName)
{
}

void SaveDataDB::Save(std::vector<std::pair<std::string, std::string>> const& a_data)
{
    std::string columns = {"("};
    std::string values = {"("};

    for(auto const& e: a_data) {
        columns += e.first;
        columns += ", ";
        values += "'";
        values += e.second;
        values += "'";
        values += ", ";
    }

    for(size_t i = 0; i < 2; ++i) {
        columns.pop_back();
        values.pop_back();
    }
    
    columns += ")";
    values += ")";

    std::string queryStr{"INSERT INTO "};

    queryStr += m_tableName;
    queryStr += " ";

    queryStr += columns;
    queryStr += " VALUES ";
    queryStr += values;

    std::lock_guard<std::mutex> guard(m_mtx);

    sql::Statement *stmt = m_dbConnection->createStatement();
    try {
        stmt->execute(queryStr);

    }
    catch (sql::SQLException const& e) {
        std::cout << "***** Error: " << e.what();
        std::cout << " MySQL code: " << e.getErrorCode();
		std::cout << " SQLState: " << e.getSQLState() << std::endl;
    }

    
}


} // namespace smart_home