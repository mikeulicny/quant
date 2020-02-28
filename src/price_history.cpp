#include "../include/price_history.hpp"

// TODO: think about changing enums to strings?


tdma::price_history::price_history(auth &auth_ref, const std::string &symbol) : p_auth(&auth_ref)
{
    curl_connection::url_set(CURLUPART_URL, TDMA_URL_BASE);
    set_symbol(symbol);
}

tdma::price_history::price_history(auth &auth_ref, const std::string &symbol, int period_value, period_type period,
        int frequency_value, frequency_type frequency) : p_auth(&auth_ref)
{
    curl_connection::url_set(CURLUPART_URL, TDMA_URL_BASE);
    set_symbol(symbol);
    set_timeframe(period_value, period, frequency_value, frequency);
}

tdma::price_history::price_history(auth &auth_ref, const std::string &symbol, long long start_timepoint, long long end_timepoint,
        int frequency_value, frequency_type frequency) : p_auth(&auth_ref)
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

void tdma::price_history::set_timeframe(int period_value, period_type period, int frequency_value, frequency_type frequency)
{    /* allowed values for:
     * period - day: 1, 2, 3, 4, 5, 10*
     *          month: 1*, 2, 3, 6
     *          year: 1*, 2, 3, 5, 10, 15, 20
     *          ytd: 1*
     */
    curl_connection::url_set(CURLUPART_QUERY, "period=" + std::to_string(period_value));
    curl_connection::url_set(CURLUPART_QUERY, "frequency=" + std::to_string(frequency_value), CURLU_APPENDQUERY);
    set_period(period);
    set_frequency(frequency);
}

void tdma::price_history::set_timeframe(long long start_date, long long end_date, int frequency_value, frequency_type frequency)
{
    /* start date and end date must be passed as milliseconds since epoch
     */
    curl_connection::url_set(CURLUPART_QUERY, "endDate=" + std::to_string(end_date));
    curl_connection::url_set(CURLUPART_QUERY, "startDate=" + std::to_string(start_date), CURLU_APPENDQUERY);
    curl_connection::url_set(CURLUPART_QUERY, "frequency=" + std::to_string(frequency_value), CURLU_APPENDQUERY);
    set_frequency(frequency); 
}

void tdma::price_history::set_period(period_type period)
{
    switch (period)
    {
        case DAY:
            curl_connection::url_set(CURLUPART_QUERY, "periodType=day", CURLU_APPENDQUERY);
            break;
        case MONTH:
            curl_connection::url_set(CURLUPART_QUERY, "periodType=month", CURLU_APPENDQUERY);
            break;
        case YEAR:
            curl_connection::url_set(CURLUPART_QUERY, "periodType=year", CURLU_APPENDQUERY);
            break;
        case YTD:
            curl_connection::url_set(CURLUPART_QUERY, "periodType=ytd", CURLU_APPENDQUERY);
            break;
    }
}

void tdma::price_history::set_frequency(frequency_type frequency)
{
    switch (frequency)
    {
        case MINUTE:
            curl_connection::url_set(CURLUPART_QUERY, "frequencyType=minute", CURLU_APPENDQUERY);
            break;
        case DAILY:
            curl_connection::url_set(CURLUPART_QUERY, "frequencyType=daily", CURLU_APPENDQUERY);
            break;
        case WEEKLY: 
            curl_connection::url_set(CURLUPART_QUERY, "frequencyType=weekly", CURLU_APPENDQUERY);
            break;
        case MONTHLY:
            curl_connection::url_set(CURLUPART_QUERY, "frequencyType=monthly", CURLU_APPENDQUERY);
            break;
    }
}
