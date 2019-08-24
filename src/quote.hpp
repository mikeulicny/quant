#pragma once

#include <iostream>
#include <rapidjson/document.h>
#include <string>
#include <vector>


namespace api
{
    class Quote {
        public:
            Quote(const std::string &buffer_input);
            ~Quote();
            
            void display();
            /*
            TODO: This all needs to be re-written to better suit access of the quote data
            */
        
        private:
            rapidjson::Document quote_doc;
            
            struct Mutual_Fund
            {    
                std::string symbol;
                std::string description;
                double close_price;
                double net_change;
                int total_volume;
                int trade_time;
                std::string exchange;
                std::string exchange_name;
                int digits;
                double year_high;
                double year_low;
                double net_asset_value;
                double pe_ratio;
                double div_amount;
                double div_yield;
                std::string div_date;
                std::string security_status;
            };  // struct Mutual_Fund

            struct Future
            {
                std::string symbol;
                double bid_price;
                double ask_price;
                double last_price;
                std::string bid_id;
                std::string ask_id;
                double high_price;
                double low_price;
                double close_price;
                std::string exchange;
                std::string description;
                std::string last_id;
                double open_price;
                double net_change;
                double percent_change;
                std::string exchange_name;
                std::string security_status;
                double open_interest;
                double mark;
                double tick;
                double tick_amount;
                std::string product;
                std::string future_price_format;
                std::string future_trading_hrs;
                bool future_is_tradable;
                double multiplier;
                bool is_active;
                double settlement_price;
                std::string active_symbol;
                std::string expiration_date;
            };   // struct Future

            struct Future_Option
            {
                std::string symbol;
                double bid_price;
                double ask_price;
                double last_price;
                double high_price;
                double low_price;
                double close_price;
                std::string description;
                double open_price;
                double net_change;
                double open_interest;
                std::string exchange_name;
                std::string security_status;
                double volatility;
                double intrinsic_value;
                double multiplier;
                int digits;
                double strike_price;
                std::string contract_type;
                std::string underlying;
                double time_value;
                double delta;
                double gamma;
                double theta;
                double vega;
                double rho;
                double mark;
                double tick;
                double tick_amount;
                bool future_is_tradable;
                std::string future_trading_hrs;
                double percent_change;
                bool is_active;
                int expiration_date;
                std::string expiration_type;
                std::string excercise_type;
                bool in_the_money;
            };   // struct Future_Options

            struct Index
            {
                std::string symbol;
                std::string description;
                double last_price;
                double open_price;
                double high_price;
                double low_price;
                double close_price;
                double net_change;
                int total_volume;
                int trade_time;
                std::string exchange;
                std::string exchange_name;
                int digits;
                double year_high;
                double year_low;
                std::string security_status;
            };   // struct Index

            struct Option
            {
                std::string symbol;
                std::string description;
                double bid_price;
                int bid_size;
                double ask_price;
                int ask_size;
                double last_price;
                int last_size;
                double open_price;
                double high_price;
                double low_price;
                double close_price;
                double net_change;
                int total_volume;
                int quote_time;
                int trade_time;
                double mark;
                double open_interest;
                double volatility;
                double intrinsic_value;
                double multiplier;
                double strike_price;
                std::string contract_type;
                std::string underlying;
                double time_value;
                std::string deliverables;
                double delta;
                double gamma;
                double theta;
                double vega;
                double rho;
                std::string security_status;
                double theoretical_option_value;
                double underlying_price;
                std::string uv_expiration_type;
                std::string exchange;
                std::string exchange_name;
                std::string settlement_type;
            };   // struct Option

            struct Forex
            {
                std::string symbol;
                double bid_price;
                double ask_price;
                double last_price;
                double high_price;
                double low_price;
                double close_price;
                std::string exchange;
                std::string description;
                double open_price;
                double net_change;
                double percent_change;
                std::string exchange_name;
                int digits;
                std::string security_status;
                double tick;
                double tick_amount;
                std::string product;
                std::string trading_hours;
                bool is_tradable;
                std::string market_maker;
                double year_high;
                double year_low;
                double mark;
            };   // struct Forex

            struct ETF
            {
                std::string symbol;
                std::string description;
                double bid_price;
                int bid_size;
                std::string bid_id;
                double ask_price;
                int ask_size;
                std::string ask_id;
                double last_price;
                int last_size;
                std::string last_id;
                double open_price;
                double high_price;
                double low_price;
                double close_price;
                double net_change;
                int total_volume;
                int quote_time;
                int trade_time;
                double mark;
                std::string exchange;
                std::string exchange_name;
                bool marginable;
                bool shortable;
                double volatility;
                int digits;
                double year_high;
                double year_low;
                double pe_ratio;
                double div_amount;
                double div_yield;
                std::string div_date;
                std::string security_status;
                double reg_market_last_price;
                int reg_market_last_size;
                double reg_market_net_change;
                int reg_market_trade_time;
            };   // struct ETF

            struct Equity
            {
                std::string symbol;
                std::string description;
                double bid_price;
                int bid_size;
                std::string bid_id;
                double ask_price;
                int ask_size;
                std::string ask_id;
                double last_price;
                int last_size;
                std::string last_id;
                double open_price;
                double high_price;
                double low_price;
                double close_price;
                double net_change;
                int total_volume;
                int quote_time;
                int trade_time;
                double mark;
                std::string exchange;
                std::string exchange_name;
                bool marginable;
                bool shortable;
                double volatility;
                int digits;
                double year_high;
                double year_low;
                double pe_ratio;
                double div_amount;
                double div_yield;
                std::string div_date;
                std::string security_status;
                double reg_market_last_price;
                int reg_market_last_size;
                double reg_market_net_change;
                int reg_market_trade_time;
                double net_percent_change;
                double mark_change;
                double mark_percent_change;
                double reg_market_percent_change;
                bool delayed;
            };   //struct Equity

            std::vector<struct Mutual_Fund> mutual_fund_quotes;
            std::vector<struct Future> future_quotes;
            std::vector<struct Future_Option> future_option_quotes;
            std::vector<struct Index> index_quotes;
            std::vector<struct Option> option_quotes;
            std::vector<struct Forex> forex_quotes;
            std::vector<struct ETF> etf_quotes;
            std::vector<struct Equity> equity_quotes;
    };  // class quote
}   // namespace api