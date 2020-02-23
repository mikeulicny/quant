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
}

tdma::price_history::price_history(auth &auth_ref, const std::string &symbol, long long start_timepoint, long long end_timepoint,
        int frequency, const std::string &frequency_type) :
    p_auth(&auth_ref), m_symbol(symbol),
    m_start_timepoint(start_timepoint),
    m_end_timepoint(end_timepoint)
{
}

tdma::price_history::~price_history()
{
}

const nlohmann::json tdma::price_history::get()
{
    curl_connection::reset();

    std::string url = "https://api.tdameritrade.com/v1/marketdata/";
    url += m_symbol;
    url += "/pricehistory?";
    if (m_period != 0)    // use period, if it is 0 use start & end timestamps
    {
        url += "period=" + std::to_string(m_period);
        url += "&periodType=" + m_period_type;
        url += "&frequency=" + std::to_string(m_frequency);
        url += "&frequencyType=" + m_frequency_type;
    }
    else if (m_period == 0)
    {
        url += "endDate=" + std::to_string(m_end_timepoint);
        url += "&startDate=" + std::to_string(m_start_timepoint);
        url += "&frequency=" + std::to_string(m_frequency);
        url += "&frequencyType=" + m_frequency_type;
    }

    if (!m_extended_hours)
        url += "&needExtendedHoursData=false";

    curl_connection::add_header(p_auth->auth_header());
    curl_connection::setopt(CURLOPT_URL, url.c_str());
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "GET");

    curl_connection::perform();

    nlohmann::json m_data = nlohmann::json::parse(curl_connection::data());
    return m_data;
}

void tdma::price_history::set_timeframe(int period, const std::string &period_type, int frequency, const std::string &frequency_type)
{
    /* allowed values for:
     * period - day: 1, 2, 3, 4, 5, 10*
     *          month: 1*, 2, 3, 6
     *          year: 1*, 2, 3, 5, 10, 15, 20
     *          ytd: 1*
     */
    if (period == 0)    // prevent user from setting period to 0, if set to 0 get request will use start & end timestamps
        m_period = 10;
    else
        m_period = period;
    m_period_type = period_type;
    m_frequency = frequency;
    m_frequency_type = frequency_type;
}

void tdma::price_history::set_timeframe(long long start_date, long long end_date, int frequency, const std::string &frequency_type)
{
    /* start date and end date must be passed as milliseconds since epoch
     * period is set to 0 (an invalid value) to properly set url during request
     */

    m_period = 0;       // if period is set to 0, get request will use start & end timestamps
    m_start_timepoint = start_date;
    m_end_timepoint = end_date;
    m_frequency = frequency;
    m_frequency_type = frequency_type;
}
