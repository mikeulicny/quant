#include "../include/auth.hpp"


tdma::auth::auth(const std::string &file_name) : m_file(file_name)
{
    read_from_file(m_file);
}

tdma::auth::~auth()
{
    write_to_file(m_file);
}

void tdma::auth::post(const bool &get_refresh)
{
    curl_connection::reset();

    std::string post_data = "access_type=";
    if (get_refresh)
    {
        post_data += "offline";
    }
    post_data += "&grant_type=refresh_token";
    post_data += "&code=&redirect_uri=&client_id=";
    post_data += m_client_id;
    post_data += "&refresh_token=";
    post_data += m_refresh_token;

    // request new codes
    curl_connection::setopt(CURLOPT_URL, "https://api.tdameritrade.com/v1/oauth2/token");
    curl_connection::setopt(CURLOPT_POSTFIELDS, post_data.c_str());
    curl_connection::setopt(CURLOPT_POSTFIELDSIZE, (long)std::strlen(post_data.c_str()));
    curl_connection::setopt(CURLOPT_CUSTOMREQUEST, "POST");

    curl_connection::perform();
 
    nlohmann::json temp_json;
    temp_json = nlohmann::json::parse(curl_connection::data());
   
    // TODO: create time class to handle verbose chrono library
    m_access_token = temp_json["access_token"].get<std::string>();
    access_expires_at = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now() + std::chrono::seconds(1800));

    if (get_refresh)
    {
        m_refresh_token = util::url_encode(temp_json["refresh_token"].get<std::string>());
        refresh_expires_at = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now() + std::chrono::hours(2160));

    // TODO: add in support for reading "scope", "token_type", and expiry times from
    // tdma json response
    } 
}

void tdma::auth::read_from_file(const std::string &file_name)
{
    long integral_access_timepoint;
    long integral_refresh_timepoint;

    std::ifstream file(file_name);
    nlohmann::json temp_json;
    file >> temp_json;
    m_client_id = temp_json["client_id"].get<std::string>();
    m_access_token = temp_json.value("access_token", "");
    m_refresh_token = temp_json["refresh_token"].get<std::string>();
    integral_access_timepoint = temp_json.value("access_expires_at", 0);
    integral_refresh_timepoint = temp_json.value("refresh_expires_at", 0);

    // convert integrals to time point
    std::chrono::duration<long> access_dur(integral_access_timepoint);
    std::chrono::duration<long> refresh_dur(integral_refresh_timepoint);
    access_expires_at = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>(access_dur);
    refresh_expires_at = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>(refresh_dur);
}

void tdma::auth::write_to_file(const std::string &file_name)
{
    // convert time points to integrals
    long integral_access_timepoint = access_expires_at.time_since_epoch().count();
    long integral_refresh_timepoint = refresh_expires_at.time_since_epoch().count();

    // populate file
    std::ofstream file(file_name);
    nlohmann::json temp_json;
    temp_json["client_id"] = m_client_id;
    temp_json["access_token"] = m_access_token;
    temp_json["refresh_token"] = m_refresh_token;
    temp_json["access_expires_at"] = integral_access_timepoint;
    temp_json["refresh_expires_at"] = integral_refresh_timepoint;
    file << std::setw(4) << temp_json << std::endl;
}

void tdma::auth::verify()
{
    if (access_expires_at < std::chrono::system_clock::now())
    {
        post();
    }

    m_auth_header = "Authorization: Bearer " + m_access_token;
}
