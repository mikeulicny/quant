#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "unique_curl.hpp"
#include "auth.hpp"
#include "query.hpp"

namespace tdma
{

class account
{
    public:
        account(auth &auth_ref, const std::string &account_id, bool positions, bool orders);
        ~account();

        void get();

        const std::string &data() const { return m_data; }

    private:
        auth *p_auth;
        std::string m_account_id;
        query m_account_fields;
        bool m_positions;
        bool m_orders;

        std::string m_data;

        unique_curl curl_handle;

}; // account class

} // tdma namespace
