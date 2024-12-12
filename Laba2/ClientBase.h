#pragma once

#include "Order.h"
#include "Client.h"
#include <vector>
#include <algorithm>

class ClientBase {
private:
    vector<Client> clientList;
    int nextClientNumber;
public:
    ClientBase(int numClients, const PromoCode& promoCode = PromoCode());
    const vector<Client>& getClientList() const;
    vector<Client>& getClientList();
    void addClient(const string& name, const PromoCode& promoCode = PromoCode());
    void removeClient(int clientNumber);
    bool checkClientOrder(int clientNumber, const Order& order);
};