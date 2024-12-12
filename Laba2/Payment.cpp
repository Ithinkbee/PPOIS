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
        cout << "������: ����� ������ �� ����� ���� �������������!" << endl;
    }
}
void Payment::setPaidImmediately(bool immediate) { 
    paidImmediately = immediate; 
}
static string paymentMethodToString(PaymentMethod method) {
    switch (method) {
    case PaymentMethod::Cash: return "��������";
    case PaymentMethod::Card: return "�� �����";
    case PaymentMethod::Online: return "������";
    default: return "����������";
    }
}
void Payment::printPaymentInfo() const {
    cout << "������ ������: " << paymentMethodToString(method) << endl;
    cout << "�����: " << fixed << setprecision(2) << amount << " ���." << endl;
    cout << "�������� �����: " << (paidImmediately ? "��" : "���") << endl;
}