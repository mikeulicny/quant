#include "../include/quote.hpp"

tdma::quote::quote(auth &auth_ref) : p_auth(&auth_ref)
{
}

tdma::quote::quote(auth &auth_ref, const std::string &symbol) : p_auth(&auth_ref)
{
    m_symbols.push_back(util::to_upper(symbol));
}

tdma::quote::~quote()
{
}

const nlohmann::json tdma::quote::get()
{
    curl_connection::reset();

    std::string url = "https://api.tdameritrade.com/v1/marketdata/quotes";
    url += "?symbol=";
    for (std::vector<std::string>::const_iterator v_iter = m_symbols.begin(); v_iter != m_symbols.end(); ++v_iter)
    {
        url += *v_iter; // symbol
        url += "%2C";   // comma
    }

    curl_connection::add_header(p_auth->auth_header());
    curl_connection::setopt(CURLOPT_URL, url.c_str());
    curl_connection::setopt(CURLOPT_HTTPHEADER, headers.list());
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "GET");

    curl_connection::perform();

    nlohmann::json m_data = nlohmann::json::parse(curl_connection::data());
    return m_data;
};

void tdma::quote::add_symbol(const std::string &symbol)
{
    m_symbols.push_back(util::to_upper(symbol));
}

void tdma::quote::clear_symbols()
{
    m_symbols.clear();
}

