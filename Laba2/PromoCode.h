#pragma once

#include <iostream>
#include <string>
#include <random>

using namespace std;

class PromoCode {
private:
    string promoCode;
    double discount;
    static const int CODE_LENGTH = 4;   // Длина промокода
    static const double MIN_DISCOUNT;   // Минимальная скидка
    static const double MAX_DISCOUNT;   // Максимальная скидка
public:
    PromoCode();
    string getPromoCode() const;
    double getDiscount() const;
    double applyDiscount(double price) const;
    void printPromoCodeInfo() const;
};
