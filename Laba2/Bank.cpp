#include "Bank.h"

void Bank::addMoney(double amount) {
    if (amount > 0) {
        money += amount;
    }
    else {
        cout << "Ошибка: сумма добавления должна быть положительной!" << endl;
    }
}
double Bank::getMoney() const {
    return money;
}