#pragma once

#include <string>
#include <curl/curl.h>
#include <fmt/format.h>

namespace tdma
{

class auth
{
    public:
        auth();
        ~auth();
        
        void post();
        const bool is_expired();

        const std::string &client_id() const {return m_client_id;}
        const std::string &access_token() const {return m_access_token;}
        const std::string &refresh_token() const {return m_refresh_token;}

    private:
        rapidjson::Document doc;
        
        std::string m_client_id;
        std::string m_access_token;
        std::string m_refresh_token;

};// auth class

}// tdma namespace
