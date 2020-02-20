#include "../include/quote.hpp"

tdma::quote::quote(auth &auth_ref) : p_auth(&auth_ref)
{
}

tdma::quote::~quote()
{
}

void tdma::quote::get()
{
    std::string url = "https://api.tdameritrade.com/v1/marketdata/quotes";
    url += "?symbol=";
    for (std::vector<std::string>::const_iterator v_iter = m_symbols.begin(); v_iter != m_symbols.end(); ++v_iter)
    {
        url += *v_iter; // symbol
        url += "%2C";   // comma
    }

    unique_slist headers;
    headers.append(p_auth->auth_header());

    curl_connection::setopt(CURLOPT_URL, url.c_str());
    curl_connection::setopt(CURLOPT_HTTPHEADER, headers.list());
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "GET");

    curl_connection::perform();

    m_data = curl_connection::data();
};

void tdma::quote::add_symbol(const std::string &symbol)
{
    m_symbols.push_back(symbol);
}

void tdma::quote::clear_symbols()
{
    m_symbols.clear();
}

