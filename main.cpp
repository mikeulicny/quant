//system defined classes
#include <iostream>
#include <curl/curl.h>
#include <readline/readline.h>
#include <readline/history.h>

//api classes
#include "api.hpp"



int main(void)
{	
	std::string USER_INPUT;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	std::cout << "Algo Trader Version 1.0.0" << std::endl;
	
	// TEST
	api::Api user;
	std::string account;
	std::string symbol;

	user.authentication();
	std::cout << "Account number:";
	std::cin >> account;
	user.get_account(account);
	std::cout << "Symbol:";
	std::cin >> symbol;
	user.get_quotes(symbol);
	
	std::cin.get();

	curl_global_cleanup();
	return 0;
}

