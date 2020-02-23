#include "../include/account.hpp"

tdma::account::account(auth &auth_ref, const std::string &account_id, const bool positions, const bool orders) : 
    p_auth(&auth_ref),
    m_account_id(account_id),
    m_positions(positions),
    m_orders(orders)
{
}

tdma::account::~account()
{
}

const nlohmann::json tdma::account::get()
{
    curl_connection::reset();

    std::string url = "https://api.tdameritrade.com/v1/accounts/";
    url += m_account_id;
    if (m_positions && m_orders)
        url += "?fields=positions%2Corders";
    else if (m_positions && !m_orders)
        url += "?fields=positions";
    else if (m_orders && !m_positions)
        url += "?fields=orders";

    curl_connection::add_header(p_auth->auth_header());
    curl_connection::setopt(CURLOPT_URL, url.c_str());
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "GET");

    curl_connection::perform();

    nlohmann::json m_data = nlohmann::json::parse(curl_connection::data());
    return m_data;
}



