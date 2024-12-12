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

    double getTemperature() const { return temperature; }
    void setTemperature(double temp) { temperature = temp; }

    double getPrecipitation() const { return precipitation; }
    void setPrecipitation(double precip) { precipitation = precip; }

    double getWindSpeed() const { return windSpeed; }
    void setWindSpeed(double wind) { windSpeed = wind; }

    double calculatePriceImpact(double basePrice) const;

    void printWeather() const;
};