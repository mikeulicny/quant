#pragma once

// debugging
#include <iostream>

#include <chrono>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>
#include <fmt/format.h>

#include "http_util.hpp"
#include "unique_curl.hpp"


namespace tdma
{

class auth
{
    public:
        auth();
        ~auth();
        
        void post(const bool &get_refresh = false);
        void write_to_file(const std::string &file_name = "credentials.json");
        const bool is_expired();
        
        const std::string &client_id() const {return m_client_id;}
        const std::string &access_token() const {return m_access_token;}
        const std::string &refresh_token() const {return m_refresh_token;}

    private:

        std::string m_client_id;
        std::string m_access_token;
        std::string m_refresh_token;
        std::chrono::steady_clock::time_point access_expires_at;
        std::chrono::steady_clock::time_point refresh_expires_at;

        unique_curl curl_handle;

};// auth class

}// tdma namespace
