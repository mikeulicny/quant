#include "../include/query.hpp"

tdma::query::query()
{
}

tdma::query::~query()
{
}

void tdma::query::append(const std::string &key, const std::string &value)
{
    m_data.emplace_back(key, value);
}

const std::string tdma::query::data()
{
    std::string temp_str;

    for (auto v_iter = m_data.begin(); v_iter != m_data.end(); ++v_iter)
    {
        temp_str.append(v_iter->first).append("=").append(v_iter->second);
        if (v_iter + 1 != m_data.end())
            temp_str.append("&");
    }
    
    return temp_str;
}
