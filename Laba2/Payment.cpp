#include "Payment.h"

PaymentMethod Payment::getMethod() const {
    return method; 
}
double Payment::getAmount() const {
    return amount; 
}
bool Payment::isPaidImmediately() const {
    return paidImmediately;
}
void Payment::setMethod(PaymentMethod newMethod) {
    method = newMethod;
}
void Payment::setAmount(double newAmount) {
    if (newAmount >= 0) {
        amount = newAmount;
    }
    else {
        cout << "Ошибка: сумма оплаты не может быть отрицательной!" << endl;
    }
}
void Payment::setPaidImmediately(bool immediate) { 
    paidImmediately = immediate; 
}
static string paymentMethodToString(PaymentMethod method) {
    switch (method) {
    case PaymentMethod::Cash: return "Наличные";
    case PaymentMethod::Card: return "По карте";
    case PaymentMethod::Online: return "Онлайн";
    default: return "Неизвестно";
    }
}
void Payment::printPaymentInfo() const {
    cout << "Способ оплаты: " << paymentMethodToString(method) << endl;
    cout << "Сумма: " << fixed << setprecision(2) << amount << " руб." << endl;
    cout << "Оплачено сразу: " << (paidImmediately ? "Да" : "Нет") << endl;
}