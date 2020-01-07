#include "unique_curl.hpp"

tdma::unique_curl::unique_curl()
{
    curl = curl_easy_init();
}

tdma::unique_curl::~unique_curl()
{
    curl_easy_cleanup(curl);
}

template <typename T>
void tdma::unique_curl::setopt(const CURLoption &option, const T &parameter)
{
    curl_easy_setopt(curl, option, parameter);
}

void tdma::unique_curl::reset()
{
    curl_easy_reset(curl);
}

void tdma::unique_curl::perform()
{
    res = curl_easy_perform(curl);
}

size_t tdma::unique_curl::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

