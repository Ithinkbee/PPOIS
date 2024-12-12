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
        vehicleCounts["����� ������"] = courier;
        vehicleCounts["������������"] = minibus;
        vehicleCounts["�������� ����������"] = car;
        vehicleCounts["��������"] = motorcycle;
        vehicleCounts["���������"] = bicycle;
    }
    void decreaseCount(const string& vehicleType);
    void increaseCount(const string& vehicleType);
    int getAvailableCount(const string& vehicleType) const;
};