#pragma once
#include "Vehicle.h"

class Bicycle : public Vehicle {
public:
    //��� ������������� ��������; ��������; ����������������; ����. ���������
    Bicycle() : Vehicle("���������", 25, 350, 5) {}
};