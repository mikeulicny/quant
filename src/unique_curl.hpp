#pragma once

#include <curl/curl.h>

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

};
