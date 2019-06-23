//system defined classes
#include <iostream>
#include <curl/curl.h>

//api classes
#include "account.hpp"



int main(void)
{	
	std::string USER_INPUT;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	std::cout << "Algo Trader Version 1.0" << std::endl;
	
	// TEST
	api::Account user;
	user.get_quotes("NVDA");
	std::cin.get();

	curl_global_cleanup();
	return 0;
}

