#include "unique_header.hpp"

tdma::unique_header::unique_header()
{

}

tdma::unique_header::~unique_header()
{
    curl_slist_free_all(slist);
}

void tdma::unique_header::append(std::string header)
{
    slist = curl_slist_append(slist, header.c_str());
}
