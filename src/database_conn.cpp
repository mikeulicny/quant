#include "../include/database_conn.hpp"

tdma::database_conn::database_conn(const std::string &conninfo)
{
    m_conn = PQconnectdb(conninfo.c_str());
}

tdma::database_conn::~database_conn()
{
    PQfinish(m_conn);
}

void tdma::database_conn::exec(const std::string &query)
{
    PQexec(m_conn, query.c_str());
}

const std::string tdma::database_conn::name()
{
    return PQdb(m_conn);
}

const std::string tdma::database_conn::user()
{
    return PQuser(m_conn);
}

const std::string tdma::database_conn::host()
{
    return PQhost(m_conn);
}

const std::string tdma::database_conn::host_addr()
{
    return PQhostaddr(m_conn);
}

const std::string tdma::database_conn::port()
{
    return PQport(m_conn);
}

const std::string tdma::database_conn::options()
{
    return PQoptions(m_conn);
}
