#include "Client.h"

void Client::addOrder(const Order & order) {
    orders.push_back(order);
}
const vector<Order>& Client::getOrders() const {
    return orders;
}
string Client::getName() const { 
    return name; 
}
int Client::getClientNumber() const { 
    return clientNumber; 
}
bool Client::checkClientOrder(Order& order) {
    for (const auto& existingOrder : orders) {
        if (existingOrder == order) {
            return true;
        }
    }
    return false;
}
void Client::removeOrder(int num) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getNumber() == num) {
            orders.erase(it);
            return;
        }
    }
}
void Client::printClientInfo() const {
    cout << "Имя клиента: " << name << endl;
    cout << "Номер клиента: " << clientNumber << endl;
    promoCode.printPromoCodeInfo();
}
bool Client::isPromoCodeValid(const string& inputPromoCode) {
    if (promoCode.getPromoCode().empty()) {
        return false;
    }
    return inputPromoCode == promoCode.getPromoCode();
}