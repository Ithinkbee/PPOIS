#pragma once
#include "Vehicle.h"

class Minibus : public Vehicle {
public:
    //��� ������������� ��������; ��������; ����������������; ����. ���������
    Minibus() : Vehicle("������������", 60, 5000, 20) {}
};