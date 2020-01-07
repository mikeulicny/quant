#pragma once

#include <curl/curl.h>

namespace tdma 
{

class unique_curl
{
    public:
        unique_curl();
        ~unique_curl();
        
        template<typename T>
        void setopt(const CURLoption &option, const T &parameter);

        void reset();
        void perform();
        
        const CURLcode &result() const {return res;}

    private:
        CURL *curl;
        CURLcode res;
        const std::string write_buffer;
        size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

}; // unique_curl class

} // tmda namespace
