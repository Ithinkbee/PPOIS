#include "Vehicle.h"

void Vehicle::printInfo() {
	cout << "Способ доставки: " << type << endl;
	cout << "Вместимость (в цене): " << capacity << endl;
	cout << "Допустимое расстояние до клиента: " << range << endl;
	cout << "Скорость: " << speed << endl;
}
string Vehicle::getType() {
	return type;
}
double Vehicle::getCapacity() {
	return capacity;
}
double Vehicle::getRange() {
	return range;
}
double Vehicle::getSpeed() {
	return speed;
}