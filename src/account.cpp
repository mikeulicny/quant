#pragma once

#include "account.hpp"


api::Account::Account()
{
    curl = curl_easy_init();
};

api::Account::~Account()
{
    curl_easy_cleanup(curl);
}

// --Public Functions--
void api::Account::cancel_order(const std::string &order_id)
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());
    
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number).append("/orders/").append(order_id);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        // TODO: Error
    }
    curl_slist_free_all(headers);
    curl_easy_reset(curl);
 
}   // cancelOrder


void api::Account::get_order(const std::string &order_id)
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number).append("/orders/").append(order_id);

    
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        // TODO: Error
    }
    // TODO: output order
    curl_slist_free_all(headers);
    curl_easy_reset(curl);
    
}   // getOrder


void api::Account::get_orders_by_path()
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number).append("/orders");

    // TODO: Set query parameters and add to url

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        // TODO: Error
    }

    // TODO: output orders
    
    curl_slist_free_all(headers);
    curl_easy_reset(curl);

}   // getOrdersByPath


void api::Account::get_orders_by_query()
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());

    // TODO: set URL
    std::string resource_url = "https://api.tdameritrade.com/v1/orders";

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    if (res != CURLE_OK)
    {
        // TODO: Error
    }
    else // TODO: Json parse
    curl_slist_free_all(headers);
    curl_easy_reset(curl);

}   // getOrdersByQuery


void api::Account::place_order()
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number).append("/orders");


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


void api::Account::replace_order()
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number).append("/orders");


    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        // TODO: Error
    }
    curl_slist_free_all(headers);
    curl_easy_reset(curl);

}   // replaceOrder


void api::Account::create_saved_order()
{
    authentication();

    // TODO: create order
    std::string post_data;  // post data will be sent as a json string

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number).append("/savedorders");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)std::strlen(post_data.c_str()));
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on createSavedOrder\n";
    }
    
    curl_slist_free_all(headers);
    curl_easy_reset(curl);

}   // createSavedOrder


void api::Account::delete_saved_order(const std::string &order_id)
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number).append("/savedorders/").append(order_id);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on deleteSavedOrder\n";
    }

    curl_slist_free_all(headers);
    curl_easy_reset(curl);

}   // deleteSavedOrder


void api::Account::get_saved_order(const std::string &order_id)
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());

    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number).append("/savedorders/").append(order_id);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on getSavedOrder\n";
    }
    else
    {
        // TODO: json parse output
    }
    read_buffer.clear();
    curl_slist_free_all(headers);
    curl_easy_reset(curl);

}   // getSavedOrder

/* void api::account::getSavedOrdersByPath()
TODO: may implement in future
*/

void api::Account::get_quotes(const std::string &symbol)
{
    authentication();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header.c_str());
    
    std::string resource_url = "https://api.tdameritrade.com/v1/marketdata/";
    resource_url.append(symbol).append("/quotes");    

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on getQuote\n";
    }
    else
    {
        // TODO: json parse output
        //  make quote object
        //  display quote
    } 
    read_buffer.clear();
    curl_slist_free_all(headers);
    curl_easy_reset(curl);

}   // getQuote

// --Private Functions--
void api::Account::authentication()
{   
    /*
    authentication function
        checks if the auth or refresh token have expired
        if (true)
            create new POST request
            get new access/refresh token
            parse from json into variable
            set new auth header
        reset curl handle
    */
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    auto auth_time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(access_token_expiry-now);
    auto refresh_time_elapsed = std::chrono::duration_cast<std::chrono::hours>(refresh_token_expiry-now);

    if (auth_time_elapsed >= std::chrono::seconds(1770))    // 29mins30secs
    {   
        std::string post_data = "access_type="; // no refresh_token
        access_token_expiry = std::chrono::steady_clock::now();

        if (refresh_time_elapsed >= std::chrono::hours(2136))   // 89 days
        {   
            post_data += "offline";  // new refresh_token
            refresh_token_expiry = std::chrono::steady_clock::now();
        }

        post_data += "&grant_type=refresh_token&code=&redirect_uri=&client_id=";
        post_data += url::urlEncode(OAuth_user_id);
        post_data += "&refresh_token=";
        post_data += url::urlEncode(refresh_token);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        // set data for post
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.tdameritrade.com/v1/oauth2/token");
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
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
            access_token = document["access_token"].GetString();
            auth_header = "Authorization: Bearer ";
            auth_header.append(access_token);

            if (document.HasMember("refresh_token"))
            {
                refresh_token = document["refresh_token"].GetString();
            }
        }

        read_buffer.clear();
        curl_slist_free_all(headers);
    }
    
    curl_easy_reset(curl);

}   // authentication

size_t api::Account::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}   // writeCallback
