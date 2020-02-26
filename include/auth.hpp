#pragma once

#include <chrono>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>

#include "curl_connection.hpp"
#include "util.hpp"

namespace tdma
{

class auth : private curl_connection
{
    public:
        auth(const std::string &file_name);

        ~auth();
        
        void post(const bool &get_refresh = false);

        void read_from_file(const std::string &file_name);

        void write_to_file(const std::string &file_name);

        void verify();

        const std::string &client_id() const { return m_client_id; }
        
        const std::string &access_token() const { return m_access_token; }
        
        const std::string &refresh_token() const { return m_refresh_token; }

        const std::string &auth_header() const { return m_auth_header; }

    private:

        const std::string m_file;

        std::string m_client_id;
        std::string m_access_token;
        std::string m_refresh_token;
        std::string m_auth_header;

        std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> access_expires_at;
        std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> refresh_expires_at;

};// auth class

}// tdma namespace
