#pragma once
#include "Vehicle.h"

class Motorcycle : public Vehicle {
public:
    //��� ������������� ��������; ��������; ����������������; ����. ���������
    Motorcycle() : Vehicle("��������", 90, 700, 10) {}
};