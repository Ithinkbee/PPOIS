#include "ClientBase.h"

ClientBase::ClientBase(int numClients, const PromoCode& promoCode)
    : nextClientNumber(1) {
    for (int i = 0; i < numClients; ++i) {
        Client client("Client" + to_string(i + 1), nextClientNumber++, promoCode);
        int numOrders = rand() % 3 + 1;
        for (int j = 0; j < numOrders; ++j) {
            Order order;
            order.setNumber(rand() % 100 + 1);
            client.addOrder(order);
        }
        clientList.push_back(client);
    }
}

const vector<Client>& ClientBase::getClientList() const {
    return clientList;
}

vector<Client>& ClientBase::getClientList() {
    return clientList;
}

void ClientBase::addClient(const string& name, const PromoCode& promoCode) {
    Client newClient(name, nextClientNumber++, promoCode);
    clientList.push_back(newClient);
}

void ClientBase::removeClient(int clientNumber) {
    auto it = std::remove_if(clientList.begin(), clientList.end(),
        [clientNumber](const Client& client) { return client.getClientNumber() == clientNumber; });
    if (it != clientList.end()) {
        clientList.erase(it, clientList.end());
        cout << "Клиент с номером " << clientNumber << " удалён.\n";
    }
    else {
        cout << "Клиент с номером " << clientNumber << " не найден.\n";
    }
}

bool ClientBase::checkClientOrder(int clientNumber, const Order& order) {
    auto it = std::find_if(clientList.begin(), clientList.end(),
        [clientNumber](const Client& client) { return client.getClientNumber() == clientNumber; });
    if (it != clientList.end()) {
        return it->checkClientOrder(const_cast<Order&>(order));
    }
    cout << "Клиент с номером " << clientNumber << " не найден.\n";
    return false;
}
