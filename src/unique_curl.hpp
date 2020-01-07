#pragma once

#include <curl/curl.h>

namespace tdma 
{

class unique_curl
{
    public:
        unique_curl();
        ~unique_curl();

        void setopt(CURLoption option, parameter)
        void reset();
        void perform();
        
        const CURLcode &result() const {return res;}

    private:
        CURL *curl;
        CURLcode res;
        
        size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

}; // unique_curl class

} // tmda namespace
