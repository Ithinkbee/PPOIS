#pragma once

#include "Payment.h"
#include "Vehicle.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Order {
private:
    int number;
    double cost;    
    int distance;  
    string vehicle;
    Payment payment;
public:
    Order(int num, double orderCost, int orderDistance, 
        const string& vehicleType, const Payment& payment)
        : number(num), cost(orderCost), distance(orderDistance),
        vehicle(vehicleType), payment(payment) {}
    Order()
        : number(1), cost(10.0), distance(1), 
        vehicle("Не указан"), payment(PaymentMethod::Cash, 0.0) {}
    bool operator==(const Order& other) const;
    void printInfo();
    int getNumber() const;
    double getCost();
    int getDistance();
    string getVehicle();
    void setVehicle(const string& vehicle);
    void setNumber(int num);
    void setPayment(const Payment& p);
    Payment getPayment() const;
};