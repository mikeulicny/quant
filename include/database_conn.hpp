#pragma once

#include <string>
#include "libpq-fe.h"

namespace tdma
{

class database_conn
{
    public:
        database_conn(const std::string &conninfo);
        ~database_conn();

        // raii class requirements
        database_conn(const database_conn&) = delete;
        database_conn&operator=(const database_conn&) = delete;

        void exec(const std::string &query);
        
        const std::string name();
        const std::string user();
        const std::string password();
        const std::string host(); 
        const std::string host_addr();
        const std::string port();
        const std::string options();
        
    private:
        PGconn *m_conn;
        PGresult *m_result;
        
};// database_conn class

} // tdma namespace
