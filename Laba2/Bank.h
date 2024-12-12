#pragma once

#include <iostream>
using namespace std;

class Bank {
private:
    double money;
public:
    Bank() : money(5000) {}
    void addMoney(double amount);
    double getMoney() const;
};