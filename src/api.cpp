#pragma once

#include "api.hpp"


api::Api::Api()
{
    // read token data into memory
    FILE* fp = fopen("tokens.json","r");
    if (fp)
    {
        char r_buffer[65536];
        rapidjson::FileReadStream is(fp, r_buffer,sizeof(r_buffer));
        rapidjson::Document doc;
        doc.ParseStream(is);
        client_id = doc["consumer_key"].GetString();
        access_token = doc["access_token"].GetString();
        refresh_token = doc["refresh_token"].GetString();
    }
    fclose(fp);
    curl = curl_easy_init();
};

api::Api::~Api()
{
    curl_easy_cleanup(curl);
}

// --Public Functions--
void api::Api::authentication(const bool &get_refresh)
{   
    std::string post_data = "access_type=";
    if (get_refresh)
    {
        post_data += "offline";
    }
    post_data += "&grant_type=refresh_token";
    post_data += "&code=&redirect_uri=&client_id=";
    post_data += client_id;
    post_data += "&refresh_token=";
    post_data += refresh_token;

    // set data for post
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.tdameritrade.com/v1/oauth2/token");
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)std::strlen(post_data.c_str()));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "Error: Authorization POST request failed\n";
    }
    else
    {
        rapidjson::Document document;
        document.Parse(read_buffer.c_str());
        
        // save access token to memory
        access_token = "Bearer ";
        access_token.append(document["access_token"].GetString());
        if (get_refresh)
        {
            // save refresh token to memory
            refresh_token = document["refresh_token"].GetString();
        }
    }
    read_buffer.clear();
    curl_easy_reset(curl);
}   // authentication

void api::Api::cancel_order(const std::string &account_id, const std::string &order_id)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_id).append("/orders/").append(order_id);

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on cancel_order\n";
    }
    curl_easy_reset(curl);
 
}   // cancel_order


void api::Api::get_order(const std::string &account_id, const std::string &order_id)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_id).append("/orders/").append(order_id);

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_order\n";
    }
    else
    {
        // TODO: display order/parse json
    }
    curl_easy_reset(curl);
    
}   // get_order


void api::Api::get_orders_by_path(const std::string &account_id)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_id).append("/orders");

    // TODO: Set query parameters and add to url

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_orders_by_path\n";
    }
    else
    {
        // TODO: output orders
    }
    curl_easy_reset(curl);

}   // get_orders_by_path


void api::Api::get_orders_by_query()
{
    // TODO: set URL
    std::string resource_url = "https://api.tdameritrade.com/v1/orders";

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_orders_by_query\n";
    }
    else // TODO: Json parse
    curl_easy_reset(curl);

}   // getOrdersByQuery


void api::Api::place_order(const std::string &account_id)
{
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_id).append("/orders");

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    /* TODO: 
    curl_easy_setopt(curl, CURLOPT_READ, read_function);
    json string must be created from multiple classes:
        instrument class
            option subclass
            mutual fund subclass
            cash equivalent subclass
            equity subclass
            fixed income subclass
        order activity class
            execution subclass
    
    transfer these set class variables into a json string
    create read function to parse json string
    attach function handle OR set string data to libcurl CURLOPT_POSTFIELDS
    */

    // TODO:
    curl_slist_free_all(headers);

}   // placeOrder


void api::Api::replace_order(const std::string &account_id)
{
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_id).append("/orders");

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    // TODO: curl_easy_setopt(curl, CURLOPT_READ, read_function);
    
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on replace_order\n";
    }
    curl_slist_free_all(headers);
    curl_easy_reset(curl);

}   // replace_order


void api::Api::create_saved_order(const std::string &account_id)
{
    // TODO: create order
    std::string post_data;  // post data will be sent as a json string

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_id).append("/savedorders");

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)std::strlen(post_data.c_str()));
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on create_saved_order\n";
    }
    curl_easy_reset(curl);

}   // create_saved_order


void api::Api::delete_saved_order(const std::string &account_id, const std::string &order_id)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_id).append("/savedorders/").append(order_id);

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on delete_saved_order\n";
    }
    curl_easy_reset(curl);

}   // delete_saved_order


void api::Api::get_saved_order(const std::string &account_id, const std::string &order_id)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_id).append("/savedorders/").append(order_id);

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_saved_order\n";
    }
    else
    {
        // TODO: json parse output
    }
    read_buffer.clear();
    curl_easy_reset(curl);

}   // get_saved_order

/* void api::account::getSavedOrdersByPath()
TODO: may implement in future
*/

void api::Api::get_account(std::string &account_number)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number);

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_account\n";
    }
    else
    {
        // TODO: json parse output
    }
    read_buffer.clear();
    curl_easy_reset(curl);
}   // get_account

void api::Api::get_accounts()
{
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts";

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_accounts\n";
    }
    else
    {
        std::cout << read_buffer << std::endl;
        // TODO: json parse output
    }
    read_buffer.clear();
    curl_easy_reset(curl);
}   // get_accounts

void api::Api::search_instruments()
{}

void api::Api::get_instrument(std::string &cusip)
{}

void api::Api::get_hours_single_market()
{}

void api::Api::get_hours_mult_markets()
{}

void api::Api::get_movers()
{}

void api::Api::get_option_chain()
{}

void api::Api::get_price_history(std::string &symbol, std::string &period, std::string &freq)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/marketdata/";
    resource_url += symbol;
    resource_url += "/pricehistory";

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_price_history\n";
    }
    else
    {
        // parse json into postgresql database
        std::cout << read_buffer << std::endl;
    }
    read_buffer.clear();
    curl_easy_reset(curl);
}   // get_price_history

void api::Api::get_quotes(const std::string &symbol)
{    
    std::string resource_url = "https://api.tdameritrade.com/v1/marketdata/";
    resource_url.append(symbol).append("/quotes");    

    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_quote\n";
    }
    else
    {
        std::cout << read_buffer << std::endl;
        Quote temp_quote(read_buffer);
        temp_quote.display();
    } 
    read_buffer.clear();
    curl_easy_reset(curl);

}   // get_quote

// TODO: implement these member functions
void api::Api::get_transaction(std::string &transaction_id)
{}

void api::Api::create_watchlist()
{}

void api::Api::delete_watchlist()
{}

void api::Api::get_watchlist()
{}

void api::Api::replace_watchlist()
{}

void api::Api::update_watchlist()
{}

// --Private Functions--
size_t api::Api::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}   // write_callback

size_t api::Api::read_callback(void *contents, size_t size, size_t nmemb, void *userp)
{

}

