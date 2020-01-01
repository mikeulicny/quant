#include "unique_curl.hpp"

unique_curl::unique_curl()
{
    curl = curl_easy_init();
}

unique_curl::~unique_curl()
{
    curl_easy_cleanup(curl);
}

void unique_curl::setopt(CURLoption &option, &parameter)
{
    curl_easy_setopt(curl, option, parameter);
}

void unique_curl::reset()
{
    curl_easy_reset(curl);
}

void unique_curl::perform()
{
    res = curl_easy_perform(curl)
}
