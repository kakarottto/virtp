#pragma once
#include <string>
#include <vector>

struct GasStation {
    std::string name;
    std::string price;
};

class FueloData
{
public:
    FueloData();
    FueloData(double lat, double lon, int radius);
    void SetData(double la, double lo, int r);
    void Fetch();
    std::string GetResponse();
    

    std::vector<GasStation> ParseStations();

private:
    std::string url = ""; 
    double lat = 42.6977;
    double lon = 23.3219;
    int radius = 10;
    std::string response;
};