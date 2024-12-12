#include "Inventory.h"

void Inventory::decreaseCount(const string& vehicleType) {
    if (vehicleCounts.find(vehicleType) != vehicleCounts.end() && vehicleCounts[vehicleType] > 0) {
        vehicleCounts[vehicleType]--;
    }
    else {
        cout << "������: ������������ ������������ ������� ���� " << vehicleType << endl;
    }
}

void Inventory::increaseCount(const string& vehicleType) {
    if (vehicleCounts.find(vehicleType) != vehicleCounts.end()) {
        vehicleCounts[vehicleType]++;
    }
    else {
        cout << "������: ������������ �������� ���� " << vehicleType << " �� �������." << endl;
    }
}

int Inventory::getAvailableCount(const string& vehicleType) const {
    auto it = vehicleCounts.find(vehicleType);
    if (it != vehicleCounts.end()) {
        return it->second;
    }
    return 0;
}