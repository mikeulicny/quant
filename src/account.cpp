#include "../include/account.hpp"

tdma::account::account(auth &auth_ref, const std::string &account_id, const bool positions, const bool orders) : 
    p_auth(&auth_ref),
    m_account_id(account_id),
    m_positions(positions),
    m_orders(orders)
{
    curl_connection::url_set(CURLUPART_URL, "https://api.tdameritrade.com/v1/accounts/" + m_account_id);
}

tdma::account::~account()
{
}

const nlohmann::json tdma::account::get()
{

    if (m_positions && m_orders)
        curl_connection::url_set(CURLUPART_QUERY, "fields=positions%2Corders"); // %2C = ,
    else if (m_positions && !m_orders)
        curl_connection::url_set(CURLUPART_QUERY, "fields=positions");
    else if (m_orders && !m_positions)
        curl_connection::url_set(CURLUPART_QUERY, "fields=orders");
    else
        curl_connection::url_set(CURLUPART_QUERY, NULL);

    curl_connection::add_header(p_auth->auth_header());
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "GET");

    curl_connection::perform();

    nlohmann::json m_data = nlohmann::json::parse(curl_connection::data());

    curl_connection::reset();

    return m_data;
}



