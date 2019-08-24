#pragma once

#include <iomanip>
#include <utility>
#include <sstream>
#include <string>
#include <vector>


 
// temp function replace with class handler for url
std::string url_encode(const std::string &input);

class Url {
    public:
        Url();
        ~Url();

        // construct url with given string
        Url(const std::string &url_str);

        Url &set_scheme(const std::string &str);

        const std::string &get_scheme() const {return scheme;}

        Url &set_host(const std::string &str);

        const std::string &get_host() const {return host;}

        Url &set_port(const std::string &str);

        const std::string &get_port() const {return port;}

        Url &set_path(const std::string &str);

        const std::string &get_path() const {return path;}

        // define Query as a vector of pairs 
        typedef std::vector<std::pair<std::string, std::string>> Query;
        
        // set query vector to the query vector q
        Url &set_query(const Query &q);

        // append key and value to query
        Url &add_query(const std::string &key, const std::string &val)
            {built = false; query.emplace_back(key, val); return *this;}

        // append key and empty value to query
        Url &add_query(const std::string &key)
            {built = false; query.emplace_back(key, ""); return *this;}

        Url &set_fragment(const std::string &str);

        const std::string &get_fragment() const {return fragment;}
    
        Url &clear();

        const char* get();
    
    private:

        void build_url();

        std::string scheme;
        std::string host;
        std::string port;
        std::string path;
        Query query;
        std::string fragment;
        std::string url;
        bool built;
}; // class Url