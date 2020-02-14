#include <iostream>
#include <string>

#include "../include/auth.hpp"

int main(int argc, char *argv[])
{
    tdma::auth user_auth;

    if (argc >= 3)
    {
        std::cout << "ERROR: too many arguments passed\n";
        return 0;
    }

    if (argc == 1 || std::string(argv[1]) == "access")
    {
        user_auth.post();
        std::cout << "new access token received\n";
    }
    else if (std::string(argv[1]) == "refresh")
    {
        user_auth.post(true);
        std::cout << "new refresh and access token received\n";
    }
    else
    {
        std::cout << "ERROR: invalid argument\nProper arguments are \"access\" or \"refresh\"\n";
    }

    return 0;
}
