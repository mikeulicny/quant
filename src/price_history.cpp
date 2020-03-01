#include "price_history.hpp"


tdma::price_history::price_history(auth &auth_ref, const std::string &symbol) : p_auth(&auth_ref)
{
    curl_connection::url_set(CURLUPART_URL, TDMA_URL_BASE);
    set_symbol(symbol);
}

tdma::price_history::price_history(auth &auth_ref,
        const std::string &symbol, 
        const int period_value, 
        const std::string &period,
        const int frequency_value, 
        const std::string &frequency) 
    : p_auth(&auth_ref)
{
    curl_connection::url_set(CURLUPART_URL, TDMA_URL_BASE);
    set_symbol(symbol);
    set_timeframe(period_value, period, frequency_value, frequency);
}

tdma::price_history::price_history(auth &auth_ref, 
        const std::string &symbol, 
        const long long start_timepoint,
        const long long end_timepoint,
        const int frequency_value, 
        const std::string &frequency) 
    : p_auth(&auth_ref)
{
    curl_connection::url_set(CURLUPART_URL, TDMA_URL_BASE);
    set_symbol(symbol);
    set_timeframe(start_timepoint, end_timepoint, frequency_value, frequency);
}

tdma::price_history::~price_history()
{
}

const nlohmann::json tdma::price_history::get()
{
    curl_connection::add_header(p_auth->auth_header());
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "GET");

    curl_connection::perform();

    nlohmann::json m_data = nlohmann::json::parse(curl_connection::data());
    
    curl_connection::reset();

    return m_data;
}

void tdma::price_history::set_symbol(const std::string &symbol)
{
    m_symbol = util::to_upper(symbol);
    curl_connection::url_set(CURLUPART_PATH, "/v1/marketdata/" + m_symbol + "/pricehistory");
}

void tdma::price_history::set_timeframe(
        const int period_value, 
        const std::string &period, 
        const int frequency_value, 
        const std::string &frequency)
{
    curl_connection::url_set(CURLUPART_QUERY, "period=" + std::to_string(period_value));
    curl_connection::url_set(CURLUPART_QUERY, "periodType=" + period, CURLU_APPENDQUERY);
    curl_connection::url_set(CURLUPART_QUERY, "frequency=" + std::to_string(frequency_value), CURLU_APPENDQUERY);
    curl_connection::url_set(CURLUPART_QUERY, "frequencyType=" frequency, CURLU_APPENDQUERY);
}

void tdma::price_history::set_timeframe(const long long start_date,
        const long long end_date,
        const int frequency_value, 
        const std::string &frequency)
{
    // start date and end date must be passed as milliseconds since epoch
    curl_connection::url_set(CURLUPART_QUERY, "endDate=" + std::to_string(end_date));
    curl_connection::url_set(CURLUPART_QUERY, "startDate=" + std::to_string(start_date), CURLU_APPENDQUERY);
    curl_connection::url_set(CURLUPART_QUERY, "frequency=" + std::to_string(frequency_value), CURLU_APPENDQUERY);
    curl_connection::url_set(CURLUPART_QUERY, "frequencyType=" + frequency, CURLU_APPENDQUERY);
}
