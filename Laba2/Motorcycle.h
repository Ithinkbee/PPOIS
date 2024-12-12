#pragma once
#include "Vehicle.h"

class Motorcycle : public Vehicle {
public:
    //Тип транспортного средства; Скорость; Грузоподъемность; Макс. Дальность
    Motorcycle() : Vehicle("Мотоцикл", 90, 700, 10) {}
};