#pragma once

#include <iostream>
#include <string>
#include <random>

using namespace std;

class PromoCode {
private:
    string promoCode;
    double discount;
    static const int CODE_LENGTH = 4;   // ����� ���������
    static const double MIN_DISCOUNT;   // ����������� ������
    static const double MAX_DISCOUNT;   // ������������ ������
public:
    PromoCode();
    string getPromoCode() const;
    double getDiscount() const;
    double applyDiscount(double price) const;
    void printPromoCodeInfo() const;
};
