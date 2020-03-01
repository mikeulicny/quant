#include "util.hpp"


const std::string util::url_encode(const std::string &s)
{
    std::ostringstream os;
    for (std::string::const_iterator ci = s.begin(); ci != s.end(); ++ci)
    {
        if ((*ci >= 'a' && *ci <= 'z') ||
            (*ci >= 'A' && *ci <= 'Z') ||
            (*ci >= '0' && *ci <= '9'))
        { // allowed
            os << *ci;
        }
        else if (*ci == ' ')
        {
            os << '+';
        }
        else
        {
            os << '%' << util::to_hex(*ci >> 4) << util::to_hex(*ci % 16);
        }
    }
    return os.str();
}

const std::string util::url_decode(const std::string &str)
{
    std::string result;
    std::string::size_type i;
    for (i = 0; i < str.size(); ++i)
    {
        if (str[i] == '+')
        {
            result += ' ';
        }
        else if (str[i] == '%' && str.size() > i + 2)
        {
            const unsigned char ch1 = util::from_hex(str[i+1]);
            const unsigned char ch2 = util::from_hex(str[i+2]);
            const unsigned char ch = (ch1 << 4) | ch2;
            result += ch;
            i += 2;
        }
        else
        {
            result += str[i];
        }
    }
    return result;
}
