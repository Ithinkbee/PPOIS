#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Inventory {
private:
    map<string, int> vehicleCounts;
public:
    Inventory(int courier, int minibus, int car, int motorcycle, int bicycle) {
        vehicleCounts["Пеший курьер"] = courier;
        vehicleCounts["Микроавтобус"] = minibus;
        vehicleCounts["Легковой автомобиль"] = car;
        vehicleCounts["Мотоцикл"] = motorcycle;
        vehicleCounts["Велосипед"] = bicycle;
    }
    void decreaseCount(const string& vehicleType);
    void increaseCount(const string& vehicleType);
    int getAvailableCount(const string& vehicleType) const;
};