#pragma once

#include <string>
#include <curl/curl.h>

namespace tdma 
{

class unique_curl
{
    public:
        unique_curl();
        ~unique_curl();
       
        // raii class requirements
        unique_curl(const unique_curl&) = delete;
        unique_curl &operator=(const unique_curl&) = delete;

        template<typename T>
        void setopt(const CURLoption &option, const T &parameter)
        {
            curl_easy_setopt(curl, option, parameter);
        }

        void reset();
        
        void perform();
        
        const CURLcode &result() const { return res; }
        const std::string &data() const { return write_buffer; }
    
    private:
        CURL *curl;
        CURLcode res;
        std::string write_buffer;
        static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

}; // unique_curl class

} // tmda namespace
