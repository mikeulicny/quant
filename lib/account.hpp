#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include <string>
#include <cstring>
#include "url.hpp"


namespace api
{
    class Account {
        public:
            Account();
            ~Account();

            void cancel_order(const std::string &order_id);
            void get_order(const std::string &order_id);
            void get_orders_by_path();
            void get_orders_by_query();
            void place_order();
            void replace_order();
            void create_saved_order();
            void delete_saved_order(const std::string &order_id);
            void get_saved_order(const std::string &order_id);
            // void get_saved_orders_by_path();
            void get_account();
            void search_instruments();
            void get_instrument(std::string &cusip);
            void get_hours_single_market();
            void get_hours_mult_markets();
            void get_movers();
            void get_option_chain();
            void get_price_history();
            // void get_quote();
            void get_quotes(const std::string &symbol);
            void get_transaction(std::string &transaction_id);
            // void get_transactions();
            void create_watchlist();
            void delete_watchlist();
            void get_watchlist();
            // void get_watchlist_for_single_account();
            void replace_watchlist();
            void update_watchlist();

        private:
            // account variables
            std::string account_number;
            std::string OAuth_user_id;
            std::string access_token;   //1083 chars
            std::string refresh_token;  //935 chars
            std::string auth_header;    //1105 chars

            // rapidjson variables
            std::string read_buffer;

            // timing points
            std::chrono::steady_clock::time_point access_token_expiry;
            std::chrono::steady_clock::time_point refresh_token_expiry;

            // curl variables
            CURL *curl;
            CURLcode res;
            // TODO: add headers to private variables?

            // internal functions
            void authentication();
            static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
            

    }; // class account

}   //namespace api
