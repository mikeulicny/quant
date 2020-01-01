#pragma once

#include <string>
#include <cstring>
#include <curl/curl.h>

namespace tdma
{

class unique_header
{
    public:
        unique_header();
        ~unique_header();
        
        void append(std::string header)
        curl_slist get() const {return slist;}

    private:
        struct curl_slist *slist = NULL;

}; // unique_header class

} // tdma namespace
