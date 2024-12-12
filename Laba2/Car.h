#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
public:
    //Тип транспортного средства; Скорость; Грузоподъемность; Макс. Дальность
    Car() : Vehicle("Легковой автомобиль", 75, 2000, 20) {}
};
