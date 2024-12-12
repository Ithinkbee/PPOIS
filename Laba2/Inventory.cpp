#include "Inventory.h"

void Inventory::decreaseCount(const string& vehicleType) {
    if (vehicleCounts.find(vehicleType) != vehicleCounts.end() && vehicleCounts[vehicleType] > 0) {
        vehicleCounts[vehicleType]--;
    }
    else {
        cout << "Ошибка: Недостаточно транспортных средств типа " << vehicleType << endl;
    }
}

void Inventory::increaseCount(const string& vehicleType) {
    if (vehicleCounts.find(vehicleType) != vehicleCounts.end()) {
        vehicleCounts[vehicleType]++;
    }
    else {
        cout << "Ошибка: Транспортное средство типа " << vehicleType << " не найдено." << endl;
    }
}

int Inventory::getAvailableCount(const string& vehicleType) const {
    auto it = vehicleCounts.find(vehicleType);
    if (it != vehicleCounts.end()) {
        return it->second;
    }
    return 0;
}