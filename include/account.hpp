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

        void set_position(bool position_flag) { m_positions = position_flag; }

        void set_order(bool order_flag) { m_orders = order_flag; }

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
