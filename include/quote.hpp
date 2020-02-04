#pragma once

#include <string>
#include <vector>
#include <initializer_list>
#include "auth.hpp"
#include "unique_slist.hpp"

namespace tdma
{

class quote
{
    public:
        quote(auth &auth_ref);
        ~quote();

        // sends a curl request to retreive quotes for each symbol
        void get();

        // adds a symbol to the list of symbols
        void add_symbol(const std::string &symbol);

        // clears the list of symbols
        void clear_symbols();

        // returns the data as a string
        const std::string &data() const { return m_data; }

    private:
        std::vector<std::string> m_symbols;
        
        auth *p_auth;
        std::string m_data;
        unique_curl curl_handle;
};// quote class

} // tdma namespace
