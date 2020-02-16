#include "../include/database_res.hpp"

tdma::database_result::database_result()
{
    m_res = nullptr;
}

tdma::database_result::~database_result()
{
    PQclear(m_res);
}
