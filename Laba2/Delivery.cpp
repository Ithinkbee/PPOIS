#include "Delivery.h"

bool Delivery::assignOrder(Order& order, const PromoCode& promoCode) {
    currentOrder = &order;
    double orderDistance = order.getDistance();
    double orderCost = order.getCost();

    double discountedCost = promoCode.applyDiscount(orderCost);
    Payment updatedPayment = order.getPayment();
    updatedPayment.setAmount(discountedCost);
    order.setPayment(updatedPayment);

    bool badWeather = weather.getTemperature() < 0 || weather.getPrecipitation() > 15.0 || weather.getWindSpeed() > 20.0;

    for (Vehicle* vehicle : vehicles) {
        if ((badWeather && (vehicle->getType() == "����� ������" || vehicle->getType() == "���������")) ||
            vehicle->getRange() < orderDistance || vehicle->getCapacity() < discountedCost) {
            continue;
        }
        order.setVehicle(vehicle->getType());
        return true;
    }

    cout << "��� ����������� ���������� ��� ���������� ������!" << endl;
    return false;
}

double Delivery::processDelivery() {
    if (!currentOrder) {
        cout << "��� ��������� ������ ��� ��������!" << endl;
        return 0;
    }

    string vehicleType = currentOrder->getVehicle();
    double distance = currentOrder->getDistance();
    double speed = 0;

    //���� �������� ������������� ��������
    for (Vehicle* vehicle : vehicles) {
        if (vehicle->getType() == vehicleType) {
            speed = vehicle->getSpeed();
            break;
        }
    }

    if (speed == 0) {
        cout << "������: ������������ �������� �� �������!" << endl;
        return 0;
    }

    double deliveryTime = ceil(distance / speed);
    cout << "����� ����� ��������� �� " << deliveryTime << " �����." << endl;
    return deliveryTime;
}

void Delivery::completeDelivery() {
    if (!currentOrder) {
        cout << "��� ��������� ������ ��� ����������!" << endl;
        return;
    }

    double basePrice = currentOrder->getPayment().getAmount();
    double finalPrice = weather.calculatePriceImpact(basePrice);
    bank->addMoney(finalPrice);

    cout << "����� ��������! �� ���� ��������� " << finalPrice << " ���." << endl;

    currentOrder = nullptr;
}

void Delivery::printAvailableVehicles() const {
    cout << "��������� ������������ ��������:" << endl;
    for (Vehicle* vehicle : vehicles) {
        vehicle->printInfo();
        cout << endl;
    }
}

