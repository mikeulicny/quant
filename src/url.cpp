#pragma once

#include "url.hpp"


// temp function
std::string url_encode(const std::string &input)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = input.begin(), n = input.end(); i!=n; ++i) 
    {
        std::string::value_type c = (*i);
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            escaped << c;
            continue;
        }
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }
    return escaped.str();
}

Url &Url::set_scheme(const std::string &str)
{
    if (str != scheme)
    {
        scheme = str;
        built = false;
        if ((scheme=="http" && port=="80") || (scheme=="https" && port=="443"))
            port="";
    }
    return *this;
}

Url &Url::set_host(const std::string &str)
{
    if (str != host)
    {
        host = str;
        built = false;
    }
    return *this;
}

Url &Url::set_port(const std::string &str)
{
    if (str != port)
    {
        port = str;
        built = false;
    }
    return *this;
}

Url &Url::set_path(const std::string &str)
{
    if (str != path)
    {
        path = str;
        built = false;
    }
    return *this;
}

Url &Url::set_query(const Query &q)
{
    if (q != query)
    {
        query = q;
        built = false;
    }
    return *this;
}

Url& Url::clear()
{
    scheme.clear();
    host.clear();
    port.clear();
    path.clear();

    return *this;
}

void Url::build_url()
{
    built = true;
    url.clear();
    if (!scheme.empty())
    {
        url.append(scheme).append(":");
    }
    if (!host.empty())
    {
        url.append("//").append(host);
        if (!port.empty())
        {
            if (!((scheme=="http"&&port=="80")||(scheme=="https"&&port=="443")))
                url.append(":").append(port);
        }
    }
    if (!path.empty())
    {
        url.append(path);
    }
    if (!query.empty())
    {
        url.append("?");
        auto iter = query.begin(), end = query.end();
        url.append(iter->first).append("=");
        if (!iter->second.empty());   // <-double check for errors
        {
            url.append(iter->second);
        }
        while (++iter!=end)
        {
            url.append("&").append(iter->first).append("=");
            if (!iter->second.empty())
            {
                url.append(iter->second);
            }
        }
    }
    if (!fragment.empty())
    {
        url.append("#").append(fragment);
    }
    built = true;
    
}

const char* Url::get()
{
    build_url();
    return url.c_str();
}

