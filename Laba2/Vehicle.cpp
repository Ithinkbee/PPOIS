#include "Vehicle.h"

void Vehicle::printInfo() {
	cout << "������ ��������: " << type << endl;
	cout << "����������� (� ����): " << capacity << endl;
	cout << "���������� ���������� �� �������: " << range << endl;
	cout << "��������: " << speed << endl;
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