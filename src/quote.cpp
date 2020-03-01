#include "quote.hpp" 

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
    std::string query = "symbol=";
    for (std::vector<std::string>::const_iterator v_iter = m_symbols.begin(); v_iter != m_symbols.end(); ++v_iter)
    {
        query += *v_iter; // symbol
        query += "%2C";   // comma
    }

    curl_connection::url_set(CURLUPART_URL, "https://api.tdameritrade.com/v1/marketdata/quotes");
    curl_connection::url_set(CURLUPART_QUERY, query);
    curl_connection::add_header(p_auth->auth_header());
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "GET");
    curl_connection::perform();
    nlohmann::json m_data = nlohmann::json::parse(curl_connection::data());
    curl_connection::reset();

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

