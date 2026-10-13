#pragma once
#include <string>


class FueloData
{
public:
	FueloData();
	FueloData(double lat, double lon, int radius);
	void SetData(double la, double lo, int r);
	void Fetch();
	std::string GetResponse();
private:
	std::string url="";	
	double lat = 42.6977;
	double lon = 23.3219;
	int radius = 10;
	std::string response;
};

