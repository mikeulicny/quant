#pragma once

#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <string>
#include <cstring>
#include "account.hpp"
#include "quote.hpp"
#include "url.hpp"


namespace api
{
    class Api {
        public:
        
            Api();
            ~Api();

            void authentication(const bool &get_refresh = false);
            void cancel_order(const std::string &account_id, const std::string &order_id);
            void get_order(const std::string &account_id, const std::string &order_id);
            void get_orders_by_path(const std::string &account_id);
            void get_orders_by_query();
            void place_order(const std::string &account_id);
            void replace_order(const std::string &account_id);
            void create_saved_order(const std::string &account_id);
            void delete_saved_order(const std::string &account_id, const std::string &order_id);
            void get_saved_order(const std::string &account_id, const std::string &order_id);
            // void get_saved_orders_by_path();
            void get_account(std::string &account_number);
            void get_accounts();
            void search_instruments();
            void get_instrument(std::string &cusip);
            void get_hours_single_market();
            void get_hours_mult_markets();
            void get_movers();
            void get_option_chain();
            void get_price_history(std::string &symbol, std::string &period, std::string &freq);
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
            // api variables
            std::string client_id;      // consumer key
            std::string access_token;   // 1083 chars
            std::string refresh_token;  // 935 chars

            // rapidjson variables
            std::string read_buffer;

            // curl variables
            CURL *curl;
            CURLcode res;
            // TODO: add headers to private variables?

            // internal functions
            static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
            static size_t read_callback(void *contents, size_t size, size_t nmemb, void *userp);
            

    }; // class account

}   //namespace api
