#include "../include/account.hpp"

tdma::account::account(auth &auth_ref, const std::string &account_id, const bool positions, const bool orders) : 
    p_auth(&auth_ref),
    m_account_id(account_id),
    m_positions(positions),
    m_orders(orders)
{
    if (positions && orders)
        m_account_fields.append("fields", "positions%2Corders");
    else if (positions && !orders)
        m_account_fields.append("fields", "positions");
    else if (!positions && orders)
        m_account_fields.append("fields", "orders");

}

tdma::account::~account()
{
}

void tdma::account::get()
{
    std::string url = "https://api.tdameritrade.com/v1/accounts/";
    url += m_account_id;
    if (m_positions || m_orders)
        url += "?" + m_account_fields.data();

    p_auth->check();

    unique_slist headers;
    headers.append(p_auth->auth_header());

    unique_curl::setopt(CURLOPT_URL, url.c_str());
    unique_curl::setopt(CURLOPT_HTTPHEADER, headers.list()); 
    unique_curl::setopt(CURLOPT_CUSTOMREQUEST, "GET");

    unique_curl::perform();

    m_data = unique_curl::data();
}



