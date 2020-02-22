#include "../include/price_history.hpp"

tdma::price_history::price_history(auth &auth_ref, const std::string &symbol) : p_auth(&auth_ref), m_symbol(symbol)
{
}

tdma::price_history::price_history(auth &auth_ref, const std::string &symbol, int period, const std::string &period_type,
        int frequency, const std::string &frequency_type) :
    p_auth(&auth_ref), m_symbol(symbol),
    m_period(period),
    m_period_type(period_type),
    m_frequency(frequency),
    m_frequency_type(frequency_type)
{
    m_query  = "period=" + std::to_string(period);
    m_query += "&periodType=" + period_type;
    m_query += "&frequency=" + std::to_string(frequency);
    m_query += "&frequencyType=" + frequency_type;
}

tdma::price_history::price_history(auth &auth_ref, const std::string &symbol, long long start_timepoint, long long end_timepoint,
        int frequency, const std::string &frequency_type) :
    p_auth(&auth_ref), m_symbol(symbol),
    m_start_timepoint(start_timepoint),
    m_end_timepoint(end_timepoint)
{
    m_query  = "endDate=" + std::to_string(end_timepoint);
    m_query += "&startDate=" + std::to_string(start_timepoint);
    m_query += "&frequency=" + std::to_string(frequency);
    m_query += "&frequencyType=" + frequency_type;
}

tdma::price_history::~price_history()
{
}

const nlohmann::json tdma::price_history::get()
{
    curl_connection::reset();

    std::string url = "https://api.tdameritrade.com/v1/marketdata/";
    url += m_symbol;
    url += "/pricehistory";
    url += "?" + m_query;

    tdma::unique_slist headers;
    headers.append(p_auth->auth_header());

    curl_connection::setopt(CURLOPT_URL, url.c_str());
    curl_connection::setopt(CURLOPT_HTTPHEADER, headers.list());
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "GET");

    curl_connection::perform();

    nlohmann::json m_data = nlohmann::json::parse(curl_connection::data());
    return m_data;

    /*  will be used elsewhere  
    m_dataframe.resize(26,6);
    for (auto &iter : json_data["candles"].items())
    {   
        m_dataframe(r,0) = iter.value()["datetime"];
        m_dataframe(r,1) = iter.value()["open"];
        m_dataframe(r,2) = iter.value()["high"];
        m_dataframe(r,3) = iter.value()["low"];
        m_dataframe(r,4) = iter.value()["close"];
        m_dataframe(r,5) = iter.value()["volume"];
    }
    */
}

void tdma::price_history::set_timeframe(int period, const std::string &period_type, int frequency, const std::string &frequency_type)
{
    /* allowed values for:
     * period - day: 1, 2, 3, 4, 5, 10*
     *          month: 1*, 2, 3, 6
     *          year: 1*, 2, 3, 5, 10, 15, 20
     *          ytd: 1*
     */
    m_query  = "period=" + std::to_string(period);
    m_query += "&periodType=" + period_type;
    m_query += "&frequency=" + std::to_string(frequency);
    m_query += "&frequencyType=" + frequency_type;
    
    /*
    m_timeframe.clear();
    m_timeframe.append("period", std::to_string(period));
    m_timeframe.append("periodType", period_type);
    m_timeframe.append("frequency", std::to_string(frequency));
    m_timeframe.append("frequencyType", frequency_type);
    */ 
}

void tdma::price_history::set_timeframe(long long start_date, long long end_date, int frequency, const std::string &frequency_type)
{
    /* start date and end date must be passed as milliseconds since epoch
     */

    m_query  = "endDate=" + std::to_string(end_date);
    m_query += "&startDate=" + std::to_string(start_date);
    m_query += "&frequency=" + std::to_string(frequency);
    m_query += "&frequencyType=" + frequency_type;
    
    /* 
    m_timeframe.clear();
    m_timeframe.append("startDate", std::to_string(start_date));
    m_timeframe.append("endDate", std::to_string(end_date));
    m_timeframe.append("frequency", std::to_string(frequency));
    m_timeframe.append("frequencyType", frequency_type);
    */
}
