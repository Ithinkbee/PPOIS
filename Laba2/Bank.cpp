#include "Bank.h"

void Bank::addMoney(double amount) {
    if (amount > 0) {
        money += amount;
    }
    else {
        cout << "������: ����� ���������� ������ ���� �������������!" << endl;
    }
}
double Bank::getMoney() const {
    return money;
}