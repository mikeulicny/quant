#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "curl_connection.hpp"
#include "auth.hpp"
#include "util.hpp"

namespace tdma
{

enum period_type 
{
    DAY,
    MONTH,
    YEAR,
    YTD
};

enum frequency_type
{
    MINUTE,
    DAILY,
    WEEKLY,
    MONTHLY
};

class price_history : private curl_connection
{
    public:
        
        price_history(auth &auth_ref, const std::string &symbol);

        price_history(auth &auth_ref, const std::string &symbol,
                int period_value, period_type period, int frequency_value, frequency_type frequency);

        price_history(auth &auth_ref, const std::string &symbol, long long start_timepoint, long long end_timepoint,
                int frequency_value, frequency_type frequency);

        ~price_history();

        // sends a curl request to obtain price history
        const nlohmann::json get();

        // set a new symbol, allowing the same curl handle to be used
        void set_symbol(const std::string &symbol);

        // TODO: set_timeframe(int, period_type, frequency_type);

        // set or change the timeframe using periods and frequency
        void set_timeframe(int period_value, period_type period, int frequency_value, frequency_type frequency);

        // set or change timeframe using start date, end date, and frequency
        void set_timeframe(long long start_date, long long end_date, int frequency_value, frequency_type frequency);

        // set extended hours flag
        void set_extended_hours(bool extended_hours) { m_extended_hours = extended_hours; }

    private:
        auth *p_auth;
        std::string m_symbol;
        std::string m_url;
        bool m_extended_hours;

        void set_period(period_type period);
        void set_frequency(frequency_type frequency);

};// price_history class

} // tdma namespace
