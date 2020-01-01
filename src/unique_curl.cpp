#include "unique_curl.hpp"

tdma::unique_curl::unique_curl()
{
    curl = curl_easy_init();
}

tdma::unique_curl::~unique_curl()
{
    curl_easy_cleanup(curl);
}

void tdma::unique_curl::setopt(CURLoption &option, &parameter)
{
    curl_easy_setopt(curl, option, parameter);
}

void tdma::unique_curl::reset()
{
    curl_easy_reset(curl);
}

void tdma::unique_curl::perform()
{
    res = curl_easy_perform(curl)
}
