#include "fuelo.h"
#include <iostream>
#include <curl/curl.h>
#include <vector>

static size_t WriteCallBack(
    void* contents,
    size_t size,
    size_t nmemb,
    void* userp
){
    size_t total = size * nmemb;
    std::string* output = static_cast<std::string*>(userp);
    output->append(static_cast<char*>(contents), total); 
    return total;
}

FueloData::FueloData()
{
    url = "https://m.fuelo.net/m/gasstations/" + std::to_string(lat) + "/" +
          std::to_string(lon) + "/" + std::to_string(radius) + "/price?lang=bg";
}

FueloData::FueloData(double lat, double lon, int radius) : lat(lat), lon(lon), radius(radius)
{
    url = "https://m.fuelo.net/m/gasstations/" + std::to_string(lat) + "/" +
          std::to_string(lon) + "/" + std::to_string(radius) + "/price?lang=bg";
}

void FueloData::SetData(double la, double lo, int r)
{
    lat = la;
    lon = lo;
    radius = r;
    url = "https://m.fuelo.net/m/gasstations/" + std::to_string(lat) + "/" +
          std::to_string(lon) + "/" + std::to_string(radius) + "/price?lang=bg";    
}   

void FueloData::Fetch()
{
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "failed to init curl\n";
        return;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK)
    {
        std::cerr << "request failed: " << curl_easy_strerror(result) << "\n";
        curl_easy_cleanup(curl);
        return;
    }
    curl_easy_cleanup(curl);
}

std::string FueloData::GetResponse() { return response; }

std::vector<GasStation> FueloData::ParseStations() {
    std::vector<GasStation> stations;
    std::string target = "bindPopup('";
    size_t pos = 0;

    while ((pos = response.find(target, pos)) != std::string::npos) {
        pos += target.length();

        size_t nameStart = response.find(">", pos);
        if (nameStart == std::string::npos) break;
        nameStart += 1;

        size_t nameEnd = response.find("</a>", nameStart);
        if (nameEnd == std::string::npos) break;
        std::string name = response.substr(nameStart, nameEnd - nameStart);

        size_t priceStart = response.find("<br>", nameEnd);
        if (priceStart == std::string::npos) break;
        priceStart += 4;

        size_t priceEnd = response.find("<br>", priceStart);
        if (priceEnd == std::string::npos) break;
        std::string price = response.substr(priceStart, priceEnd - priceStart);

        stations.push_back({name, price});
        pos = priceEnd;
    }

    return stations;
}