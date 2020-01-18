#include "auth.hpp"

tdma::auth::auth()
{
    std::ifstream file("credentials.json");
    json temp_json;
    file >> temp_json;

    client_id = temp_json["client_id"].get<std::string>();
    m_access_token = temp_json["access_token"].get<std::string>();
    m_refresh_token = temp_json["refresh_token"].get<std::string>();
    access_expires_at = temp_json["access_expires_at"].get<std::chrono::steady_clock::time_point>();
    refresh_expires_at = temp_json["refresh_expires_at"].get<std::chrono::steady_clock::time_point>();
}

tdma::auth::~auth()
{
    write_to_file();
}

void tdma::auth::post(const bool &get_refresh)
{
    // request new codes
    curl_handle.setopt(CURLOPT_URL, "https://api.tdameritrade.com/v1/oauth2/token");
    curl_handle.setopt(CURLOPT_POSTFIELDS, post_data.c_str());
    curl_handle.setopt(CURLOPT_POSTFIELDSIZE, (long)std::strlen(post_data.c_str()));
    curl_handle.setopt(CURLOPT_CUSTOMREQUEST, "POST");

    curl_handle.perform();
    
    if (curl_handle.result() != CURLE_OK)
    {
        return;
    }

    temp_json = json::parse(curl_handle.data());
    
    client_id = temp_json["client_id"].get<std::string>();
    m_access_token = temp_json["access_token"].get<std::string>();
    access_expires_at = std::chrono::steady_clock::now() + std::chrono::minutes(29);

    if (get_refresh)
    {
        m_refresh_token = temp_json["refresh_token"].get<std::string>();
        refresh_expires_at = std::chrono::steady_clock::now() + std::chrono::hours(2159);
    }
    
}

void tdma::auth::write_to_file()
{
    std::ofstream file("credentials.json");
    json temp_json;
    temp_json["client_id"] = m_client_id;
    temp_json["access_token"] = m_access_token;
    temp_json["refresh_token"] = m_refresh_token;
    temp_json["access_expires_at"] = access_expires_at;
    temp_json["refresh_expires_at"] = refresh_expires_at;
    file << temp_json << std::endl;
}

const bool tmda::auth::is_expired()
{
    
}
