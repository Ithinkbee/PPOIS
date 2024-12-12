#pragma once

#include "Order.h"
#include "Client.h"
#include "ClientBase.h"
#include "Inventory.h"
#include "Minibus.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bicycle.h"
#include "OnFoot.h"
#include "Payment.h"
#include "PromoCode.h"
#include "Weather.h"
#include "Bank.h"
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

class Delivery {
private:
    vector<Vehicle*> vehicles; 
    Order* currentOrder;      
    Bank* bank;               
    Weather weather;          

public:
    Delivery(vector<Vehicle*> availableVehicles, Bank* bankRef, const Weather& currentWeather)
        : vehicles(availableVehicles), currentOrder(nullptr), bank(bankRef), weather(currentWeather) {}

    bool assignOrder(Order& order, const PromoCode& promoCode);

    double processDelivery();

    void completeDelivery();

    void printAvailableVehicles() const;
};