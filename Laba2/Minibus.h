#pragma once
#include "Vehicle.h"

class Minibus : public Vehicle {
public:
    //Тип транспортного средства; Скорость; Грузоподъемность; Макс. Дальность
    Minibus() : Vehicle("Микроавтобус", 60, 5000, 20) {}
};