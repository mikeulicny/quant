#pragma once

#include <string>
#include "libpq-fe.h"

namespace tdma
{

class database
{
    public:
        database(const std::string &conninfo);
        ~database();

        // raii class requirements
        database(const database&) = delete;
        database&operator=(const database&) = delete;

        void exec(const std::string &query);

        const std::string name();
        const std::string user();
        const std::string &password() const { return m_password; }
        const std::string &host() const { return m_host; }
        const std::string &host_addr() const { return m_host_address; }
        const std::string &port() const { return m_port; }
        const std::string &options() const { return m_options; }
        
        // TODO: add member functions for status data
    private:
        PGconn *m_conn;
        PGresult *m_res;
        
        // make seperate class for database requests?
        // PGresult *m_res;
        
};// database class

} // tdma namespace
