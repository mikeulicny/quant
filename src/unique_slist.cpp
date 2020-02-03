#include "../include/unique_slist.hpp"

tdma::unique_slist::unique_slist()
{
    m_list = NULL;
}

tdma::unique_slist::~unique_slist()
{
    curl_slist_free_all(m_list);
}

void tdma::unique_slist::append(const std::string &str)
{
    m_list = curl_slist_append(m_list, str.c_str());
}

void tdma::unique_slist::clear()
{
    curl_slist_free_all(m_list);
    m_list = NULL;
}
