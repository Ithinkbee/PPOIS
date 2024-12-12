#include "pch.h"
#include "../PPOISlaba2/Weather.h"
#include "../PPOISlaba2/Weather.cpp"
#include <sstream>

TEST(WeatherTest, CalculatePriceImpact) {
    Weather weather;
    EXPECT_DOUBLE_EQ(100.0, weather.calculatePriceImpact(100.0));
    weather.setTemperature(-5.0);
    EXPECT_DOUBLE_EQ(120.0, weather.calculatePriceImpact(100.0)); 

    weather.setTemperature(20.0); //температуру обратно к 20C
    EXPECT_DOUBLE_EQ(100.0, weather.calculatePriceImpact(100.0)); 
    weather.setPrecipitation(15.0);
    EXPECT_DOUBLE_EQ(115.0, weather.calculatePriceImpact(100.0)); 

    weather.setPrecipitation(0.0); //осадки к нулю
    EXPECT_DOUBLE_EQ(100.0, weather.calculatePriceImpact(100.0)); 
    weather.setWindSpeed(20.0);
    EXPECT_DOUBLE_EQ(110.0, weather.calculatePriceImpact(100.0));
}
