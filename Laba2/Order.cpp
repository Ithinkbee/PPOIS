#include "Order.h"
#include "Payment.h"

bool Order::operator==(const Order& other) const {
    return number == other.number &&
        cost == other.cost &&
        distance == other.distance;
}
void Order::printInfo() {
    cout << "----------------------------------------" << endl;
    cout << "���������� � ������:" << endl;
    cout << "����� ������: " << number << endl;
    cout << "����� ������: " << cost << " ���." << endl;
    cout << "���������� �� �������: " << distance << " ��." << endl;
    cout << "��� ��������: " << vehicle << endl;
    cout << "----------------------------------------" << endl;
    payment.printPaymentInfo();
    cout << "----------------------------------------" << endl;
}
int Order::getNumber() const {
    return number;
}
void Order::setNumber(int num) {
    this->number = num;
}
double Order::getCost() {
    return cost;
}
int Order::getDistance() {
    return distance;
}
string Order::getVehicle() {
    return vehicle;
}
void Order::setVehicle(const string& vehicle) {
    if (!vehicle.empty()) {
        this->vehicle = vehicle;
    }
    else {
        cout << "������: ��� ���������� �� ����� ���� ������!" << endl;
    }
}
void Order::setPayment(const Payment& newPayment) { 
    payment = newPayment; 
}
Payment Order::getPayment() const {
    return payment;
}