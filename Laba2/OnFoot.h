#pragma once
#include "Vehicle.h"

class OnFoot : public Vehicle {
public:
    //��� ������������� ��������; ��������; ����������������; ����. ���������
    OnFoot() : Vehicle("����� ������", 5, 350, 2) {}
};