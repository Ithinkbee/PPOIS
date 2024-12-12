#pragma once
#include "Vehicle.h"

class Bicycle : public Vehicle {
public:
    //Тип транспортного средства; Скорость; Грузоподъемность; Макс. Дальность
    Bicycle() : Vehicle("Велосипед", 25, 350, 5) {}
};