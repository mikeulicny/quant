#pragma once

#include <string>
#include <curl/curl.h>

namespace tdma 
{

class curl_connection
{
    public:
        curl_connection();

        virtual ~curl_connection();
       
        // raii class requirements
        curl_connection(const curl_connection&) = delete;

        curl_connection &operator=(const curl_connection&) = delete;

        template<typename T>
        void setopt(const CURLoption &option, const T &parameter)
        {
            curl_easy_setopt(curl_handle, option, parameter);
        }

        void reset();
        
        void perform();
        
        const std::string &data() const { return write_buffer; }
    
    private:
        static struct curl_init 
        {
            // curl global environment handler
            curl_init() { curl_global_init(CURL_GLOBAL_ALL); }
            ~curl_init() { curl_global_cleanup(); }
        }curl_environment;

        CURL *curl_handle;
        std::string write_buffer;
        static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

}; // unique_curl class

} // tmda namespace
