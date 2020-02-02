#include "../include/account.hpp"

tdma::account::account(auth &auth_ref, const std::string &account_id, bool positions, bool orders) : 
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
    
    p_auth->check();

    struct curl_slist *list = NULL;
    list = curl_slist_append(list, p_auth->auth_header().c_str());

    curl_handle.setopt(CURLOPT_URL, url.c_str());
    curl_handle.setopt(CURLOPT_HTTPHEADER, list); 
    curl_handle.setopt(CURLOPT_CUSTOMREQUEST, "GET");
    
    curl_handle.perform();

    m_data = curl_handle.data();

    curl_slist_free_all(list); 
}



