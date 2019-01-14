#pragma once

#include <iostream>
#include <rapidjson/document.h>
#include <string>


namespace api
{
    class Quote
    {
        public:
            Quote(const std::string &buffer_input);
            ~Quote();

    };  // class quote

    // Change this to structs??
    class Mutual_Fund : Quote
    {
        public:
            Mutual_Fund();
            ~Mutual_Fund();

            void displayMutualFund();

        private:
            std::string symbol;
            std::string description;
            double close_price;
            double net_change;
            int total_volume;
            int trade_time_long;
            std::string exchange;
            std::string exchange_name;
            int digits;
            double year_high;
            double year_low;
            double nAV;
            double pe_ratio;
            double div_amount;
            double div_yield;
            std::string div_date;
            std::string security_status;
    };  // class mutualFund


}   // namespace api