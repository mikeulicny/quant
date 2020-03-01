#ifndef TDMA_ACCOUNT_H
#define TDMA_ACCOUNT_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "curl_connection.hpp"
#include "auth.hpp" 

namespace tdma
{

class account : private curl_connection
{
    public:

        account(auth &auth_ref, const std::string &account_id, const bool positions, const bool orders);
        
        ~account();

        void set_position(const bool position_flag) { m_positions = position_flag; }

        void set_order(const bool order_flag) { m_orders = order_flag; }

        // sends a curl request to retreive account details
        const nlohmann::json get();

    private:
        std::string m_account_id;
        bool m_positions;
        bool m_orders;

        auth *p_auth;

}; // account class

} // tdma namespace

#endif // TDMA_ACCOUNT_H
