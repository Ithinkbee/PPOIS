#pragma once
#include "Vehicle.h"

class OnFoot : public Vehicle {
public:
    //Тип транспортного средства; Скорость; Грузоподъемность; Макс. Дальность
    OnFoot() : Vehicle("Пеший курьер", 5, 350, 2) {}
};