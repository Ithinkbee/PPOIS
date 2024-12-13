#pragma once

#include <iostream>
#include <string>

using namespace std;

class Vehicle {
private:
	string type;
	double capacity;
	double range;
	double speed;
public:
	//Тип транспорта; Скорость; Вместимость; Дальность
	Vehicle(string vehicleType, double vehicleSpeed, double vehicleCapacity, double vehicleRange)
		: type(vehicleType), speed(vehicleSpeed), capacity(vehicleCapacity), range(vehicleRange) {};
	void printInfo();
	string getType();
	double getCapacity();
	double getRange();
	double getSpeed();
};