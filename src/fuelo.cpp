#include <fuelo.h>
#include <iostream>
#include <curl/curl.h>
#include <sstream>
static size_t WriteCallBack(
	void* contents,
	size_t size,
	size_t nmemb,
	void* userp
){
	size_t total = size*nmemb;
	std::string* output = static_cast<std::string*>(userp);
	output->append(static_cast<char*>(contents),total); 
	return total;
}

FueloData::FueloData()
{
	url = "https://m.fuelo.net/m/gasstations/"+std::to_string(lat)+"/"+
			std::to_string(lon)+"/"+std::to_string(radius)+"/price?lang=bg";
}
FueloData::FueloData(double lat, double lon, int radius) : lat(lat), lon(lon), radius(radius)
{
	url = "https://m.fuelo.net/m/gasstations/"+std::to_string(lat)+"/"+
			std::to_string(lon)+"/"+std::to_string(radius)+"/price?lang=bg";
}
void FueloData::SetData(double la, double lo, int r)
{
	lat = la;
	lon = lo;
	radius=r;
	url = "https://m.fuelo.net/m/gasstations/"+std::to_string(lat)+"/"+
			std::to_string(lon)+"/"+std::to_string(radius)+"/price?lang=bg";	
}	
void FueloData::Fetch()
{
	CURL* curl = curl_easy_init();
	if(!curl)
	{
		std::cerr<<"failed to init curl\n";
		return;
	}
	curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteCallBack);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response);
	curl_easy_setopt(curl,CURLOPT_USERAGENT,"Mozilla/5.0");
	curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1L);
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,10L);
	CURLcode result = curl_easy_perform(curl);
	if(result!=CURLE_OK)
	{
		std::cerr<<"request failed: "<<curl_easy_strerror(result)<<"\n";
		curl_easy_cleanup(curl);
		return;
	}
	long status = 0;
	curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&status);
	curl_easy_cleanup(curl);
}
std::string FueloData::GetResponse(){return response;}
