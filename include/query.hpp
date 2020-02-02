#pragma once

#include <utility>
#include <string>
#include <vector>

namespace tdma
{

class query
{
    public:
        query();
        ~query();

        void append(const std::string &key, const std::string &value);

        const std::string data();

    private:
        std::vector<std::pair<std::string, std::string>> m_data;

};// query class

} // tdma namespace
