#pragma once

#include <string>
#include <vector>
//#include <initializer_list>

#include "auth.hpp"
#include "curl_connection.hpp"
#include "util.hpp"
#include "unique_slist.hpp"

namespace tdma
{

class quote : private curl_connection
{
    public:

        quote(auth &auth_ref);

        quote(auth &auth_ref, const std::string &symbol);

        ~quote();

        // sends a curl request to retreive quotes for each symbol
        const nlohmann::json get();

        // adds a symbol to the list of symbols
        void add_symbol(const std::string &symbol);

        // clears the list of symbols
        void clear_symbols();

    private:

        auth *p_auth;
        std::vector<std::string> m_symbols;
        
};// quote class

} // tdma namespace
