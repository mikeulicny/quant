//system defined classes
#include <iostream>
#include <curl/curl.h>

//api classes
#include "account.hpp"



int main(void)
{	
	std::string USER_INPUT;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	std::cout << "Algo Trader Version 1.0.0" << std::endl;
	
	// TEST
	// create account object
	api::Account user;
	// call function on account
	user.get_quotes("NVDA");



	// wait for button press
	std::cin.get();

	curl_global_cleanup();
	return 0;
}

