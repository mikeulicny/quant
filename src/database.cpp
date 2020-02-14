#include "database.hpp"

tdma::database::database(const std::string &conninfo)
{
    m_conn = PQconnectdb(conninfo.c_str());
    m_res = nullptr;
}

tdma::database::~database()
{
    PQclear(m_res);
    PQfinish(m_conn);
}

void tdma::database::exec(const std::string &query)
{
    PQclear(m_res);
    m_res = PQexec(m_conn, query.c_str());
}

const std::string tdma::database::name()
{
    return PQdb(m_conn);
}

const std::string tdma::database::user()
{
    return PQuser(m_conn);
}

const std::string tdma::database::host()
{
    return PQhost(m_conn);
}

const std::string tdma::database::host_addr()
{
    return PQhostaddr(m_conn);
}

const std::string tdma::database::port()
{
    return PQport(m_conn);
}

const std::string tdma::database::options()
{
    return PQoptions(m_conn);
}
