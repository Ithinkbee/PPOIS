#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
public:
    //��� ������������� ��������; ��������; ����������������; ����. ���������
    Car() : Vehicle("�������� ����������", 75, 2000, 20) {}
};
