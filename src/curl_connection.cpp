#include <curl_connection.hpp>


tdma::curl_connection::curl_init tdma::curl_connection::curl_environment;

tdma::curl_connection::curl_connection() : 
    curl_handle(curl_easy_init()),
    url_handle(curl_url()),
    header_slist(NULL)
{
}

tdma::curl_connection::~curl_connection()
{
    curl_slist_free_all(header_slist);
    curl_url_cleanup(url_handle);
    curl_easy_cleanup(curl_handle);
}
 
void tdma::curl_connection::reset()
{
    clear_headers();
    write_buffer.clear();
    curl_easy_reset(curl_handle);
}

void tdma::curl_connection::add_header(const std::string &str)
{
    header_slist = curl_slist_append(header_slist, str.c_str());
}

void tdma::curl_connection::clear_headers()
{
    curl_slist_free_all(header_slist);
    header_slist = NULL;
}

void tdma::curl_connection::url_set(const CURLUPart &part, const std::string &parameter, unsigned int flag)
{
    curl_url_set(url_handle, part, parameter.c_str(), flag);
}

void tdma::curl_connection::perform()
{
    // default curl settings
    curl_easy_setopt(curl_handle, CURLOPT_CURLU, url_handle);
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, header_slist);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &write_buffer);

    CURLcode result = curl_easy_perform(curl_handle);
    if (result != CURLE_OK)
    {
        // TODO: error handling
    }
    
}

size_t tdma::curl_connection::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

