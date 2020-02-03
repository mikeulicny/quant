#pragma once

#include <string>
#include <curl/curl.h>

namespace tdma
{

class unique_slist
{
    public:
        unique_slist();
        ~unique_slist();

        // raii class requirements
        unique_slist(const unique_slist&) = delete;
        unique_slist &operator=(const unique_slist&) = delete;

        void append(const std::string &str);

        void clear();

        const struct curl_slist* list() const { return m_list; }

    private:
        struct curl_slist *m_list;
};// unique_slist class

} // tdma namespace
