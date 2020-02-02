#include "../include/unique_curl.hpp"

tdma::unique_curl::unique_curl()
{
    curl = curl_easy_init();
}

tdma::unique_curl::~unique_curl()
{
    curl_easy_cleanup(curl);
}

void tdma::unique_curl::reset()
{
    write_buffer.clear();
    curl_easy_reset(curl);
}

void tdma::unique_curl::perform()
{
    write_buffer.clear();

    // default curl settings
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_buffer);

    res = curl_easy_perform(curl);
}

size_t tdma::unique_curl::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

