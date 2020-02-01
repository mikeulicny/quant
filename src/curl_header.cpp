#include "curl_header.hpp"

tdma::curl_header::curl_header()
{
    m_slist = NULL;
}

tdma::curl_header::~curl_header()
{
    curl_slist_free_all(m_slist);
}

void tdma::curl_header::append(const std::string &header)
{
    slist = curl_slist_append(slist, header.c_str());
}
