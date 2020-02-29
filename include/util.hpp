#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <sstream>
#include <string>

// TODO: re-format file to follow consistent syntax


namespace util 
{

const std::string url_encode(const std::string &s);

const std::string url_decode(const std::string &str);

inline unsigned char to_hex(unsigned char x)
{
    return x + (x > 9 ? ('A' - 10) : '0');
}

inline unsigned char from_hex(unsigned char ch)
{
    if (ch <= '9' && ch >= '0')
        ch -= '0';
    else if (ch <= 'f' && ch >= 'a')
        ch -= 'a' - 10;
    else if (ch <= 'F' && ch >= 'A')
        ch -= 'A' - 10;
    else
        ch = 0;
    return ch;
}

inline std::string to_upper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c){ return std::toupper(c); } );
    return str;
}

} // util namespace

#endif // UTIL_H
