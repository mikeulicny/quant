#pragma once

#include <string>

#include "database_conn.hpp"
#include "libpq-fe.h"

namespace tdma
{

class database_result
{
    public:
        database_result();
        ~database_result();

        // raii class requirements
        database_result(const database_result&) = delete;
        database_result&operator=(const database_result&) = delete;

    private:
        PGresult *m_res;

};// database_res class

} // tdma namespace
