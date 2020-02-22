#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "curl_connection.hpp"
#include "unique_slist.hpp"
#include "auth.hpp"


namespace tdma
{

class price_history : private curl_connection
{
    public:
        
        price_history(auth &auth_ref, const std::string &symbol);

        price_history(auth &auth_ref, const std::string &symbol,
                int period, const std::string &period_type, int frequency, const std::string &frequency_type);

        price_history(auth &auth_ref, const std::string &symbol, long long start_timepoint, long long end_timepoint,
                int frequency, const std::string &frequency_type);

        ~price_history();

        // sends a curl request to obtain price history
        const nlohmann::json get();

        // set a new symbol, allowing the same curl handle to be used
        void set_symbol(const std::string &symbol) { m_symbol = util::to_upper(symbol); }

        // set or change the timeframe using periods and frequency
        void set_timeframe(int period, const std::string &period_type, int frequency, const std::string &frequency_type);

        // set or change timeframe using start date, end date, and frequency
        void set_timeframe(long long start_date, long long end_date, int frequency, const std::string &frequency_type);

        // set extended hours flag
        void set_extended_hours(bool extended_hours) { m_extended_hours = extended_hours; }

    private:
        auth *p_auth;
        std::string m_symbol;
        int m_period;
        std::string m_period_type;
        int m_frequency;
        std::string m_frequency_type;
        long long m_start_timepoint;
        long long m_end_timepoint;
        bool m_extended_hours;

};// price_history class

} // tdma namespace
