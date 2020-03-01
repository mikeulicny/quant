#ifndef TDMA_PRICE_HISTORY_H
#define TDMA_PRICE_HISTORY_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "curl_connection.hpp"
#include "auth.hpp"
#include "util.hpp"

// TODO: implement finance namespace for constexpr variables

namespace tdma
{

class price_history : private curl_connection
{
    public:
       
        price_history(auth &auth_ref, const std::string &symbol);

        price_history(auth &auth_ref,
                const std::string &symbol,
                const int period_value,
                const std::string &period,
                const int frequency_value,
                const std::string &frequency);

        price_history(auth &auth_ref,
                const std::string &symbol,
                const long long start_timepoint,
                const long long end_timepoint,
                const int frequency_value, 
                const std::string &frequency);

        ~price_history();

        // sends a curl request to obtain price history
        const nlohmann::json get();

        // set a new symbol, this sets a new path in the url_handle only
        void set_symbol(const std::string &symbol);

        // TODO: set_timeframe(int, period_type, frequency_type);

        // set or change the timeframe using periods and frequency
        void set_timeframe(
                const int period_value, 
                const std::string &period, 
                const int frequency_value, 
                const std::string &frequency);

        // set or change timeframe using start date, end date, and frequency
        void set_timeframe(
                const long long start_date, 
                const long long end_date, 
                const int frequency_value, 
                const std::string &frequency);

        // set extended hours flag
        void set_extended_hours(const bool extended_hours) { m_extended_hours = extended_hours; }

    private:
        auth *p_auth;
        std::string m_symbol;
        std::string m_url;
        bool m_extended_hours;

};// price_history class

} // tdma namespace

#endif // TDMA_PRICE_HISTORY_H
