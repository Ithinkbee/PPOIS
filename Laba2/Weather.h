#pragma once

#include <iostream>
#include <string>
using namespace std;

class Weather {
private:
    double temperature;   // в градусах Цельсия
    double precipitation; // осадки в мм
    double windSpeed;

public:
    Weather(double temp = 20.0, double precip = 0.0, double wind = 0.0)
        : temperature(temp), precipitation(precip), windSpeed(wind) {}
    double getTemperature() const;
    void setTemperature(double temp);
    double getPrecipitation() const;
    void setPrecipitation(double precip);
    double getWindSpeed() const;
    void setWindSpeed(double wind);
    double calculatePriceImpact(double basePrice) const;
    void printWeather() const;
};