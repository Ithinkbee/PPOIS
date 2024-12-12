#pragma once

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

enum class PaymentMethod {
    Cash,      
    Card,       
    Online      
};
class Payment {
private:
    PaymentMethod method;
    double amount; //������ >= ������ ���� ��� ������ (����� ����� ���� ������ �����)  
    bool paidImmediately; //true - ������ ��������� �����, false - ����� ��������
public:
    Payment()
        : method(PaymentMethod::Cash), amount(0.0), paidImmediately(false) {}
    Payment(PaymentMethod method, double amount)
        : method(method), amount(amount) {
        if (method == PaymentMethod::Online) {
            paidImmediately = true;
        }
        else {
            paidImmediately = false;
        }
    }
    PaymentMethod getMethod() const;
    double getAmount() const;
    bool isPaidImmediately() const;
    void setMethod(PaymentMethod newMethod);
    void setAmount(double newAmount);
    void setPaidImmediately(bool immediate);
    void printPaymentInfo() const;
};
