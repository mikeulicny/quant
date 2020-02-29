#ifndef TDMA_CURL_CONNECTION_H
#define TDMA_CURL_CONNECTION_H

#include <string>
#include <curl/curl.h>

namespace tdma 
{

class curl_connection
{
    public:
        curl_connection();

        virtual ~curl_connection();
      
        // remove copy constructor - RAII
        curl_connection(const curl_connection&) = delete;

        // remove assignment operator - RAII
        curl_connection &operator=(const curl_connection&) = delete;

        template<typename T>
        void setopt(const CURLoption &option, const T &parameter)
        {
            curl_easy_setopt(curl_handle, option, parameter);
        }

        void reset();
        
        void add_header(const std::string &str);

        void clear_headers();

        void url_set(const CURLUPart &part, const std::string &parameter, unsigned int flag = 0);
        
        /* url get function is not required at this time
        void url_get(const CURLUpart &part, unsigned int flag)
        {
            // std::string str = curl_url_get();
            // return str
        }
        */

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
        CURLU *url_handle;
        struct curl_slist *header_slist;

        std::string write_buffer;
        static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

}; // unique_curl class

} // tmda namespace

#endif // TDMA_CURL_CONNECTION_H
