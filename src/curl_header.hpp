#pragma once

#include <string>
#include <cstring>
#include <curl/curl.h>

namespace tdma
{

class curl_header 
{
    public:
        curl_header();
        ~curl_header();

        // raii class requirements
        curl_header(const curl_header&) = delete;
        curl_header &operator=(const unique_curl&) = delete;
        
        void append(const std::string &header);

        const curl_slist &slist() const { return slist; }

    private:
        struct curl_slist *m_slist;

}; // Curl_header class

} // tdma namespace
