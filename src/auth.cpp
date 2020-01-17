#include "tokens.hpp"

tdma::auth::auth()
{
    FILE* fp = fopen("credentials.json", "r");
    if (fp)
    {
        char r_buffer[65536];
        rapidjson::FileReadStream is(fp, r_buffer, sizeof(r_buffer));
        rapidjson::Document doc;
        doc.ParseStream(is);
        client_id = doc["consumer_key"].GetString();
        access_token = doc["access_token"].GetString();
        refresh_token = doc["refresh_token"].GetString();
    }
    fclose(fp);
}

tdma::auth::~auth()
{
    // load data to database
}

void tdma::auth::post(const bool &get_refresh)
{
    // request new codes
    curl_handle.setopt(CURLOPT_URL, "https://api.tdameritrade.com/v1/oauth2/token");
    curl_handle.setopt(CURLOPT_NOPROGRESS, 1L);
    curl_handle.setopt(CURLOPT_POSTFIELDS, post_data.c_str());
    curl_handle.setopt(CURLOPT_POSTFIELDSIZE, (long)std::strlen(post_data.c_str()));
    curl_handle.setopt(CURLOPT_CUSTOMREQUEST, "POST");

    curl_handle.perform();
}

const bool tmda::auth::is_expired()
{
    
}
