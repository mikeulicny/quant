#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "curl_connection.hpp"
#include "unique_slist.hpp"
#include "auth.hpp"
#include "query.hpp"

namespace tdma
{

class account : private unique_curl
{
    public:
        account(auth &auth_ref, const std::string &account_id, const bool positions, const bool orders);
        ~account();

        // sends a curl request to retreive account details
        const nlohmann::json get();

    private:
        std::string m_account_id;
        query m_account_fields;
        bool m_positions;
        bool m_orders;

        auth *p_auth;

}; // account class

} // tdma namespace
