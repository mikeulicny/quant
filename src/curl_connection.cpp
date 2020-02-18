#include "../include/curl_connection.hpp"


curl_connection::curl_init curl_connection::curl_environment;

tdma::curl_connection::curl_connection() : curl_handle(curl_easy_init())
{
}

tdma::curl_connection::~curl_connection()
{
    curl_easy_cleanup(curl_handle);
}

void tdma::curl_connection::reset()
{
    write_buffer.clear();
    curl_easy_reset(curl_handle);
}

void tdma::curl_connection::perform()
{
    write_buffer.clear();

    // default curl settings
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &write_buffer);

    CURLcode result = curl_easy_perform(curl_handle);
    if (result != CURL_OK)
    { 
        // TODO: error handling
    }
    
}

size_t tdma::curl_connection::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

