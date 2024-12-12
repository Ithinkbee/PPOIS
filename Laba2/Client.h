#pragma once

#include "PromoCode.h"
#include "Order.h"
#include <vector>

class Client {
private:
	string name;
	int clientNumber;
	PromoCode promoCode;
	vector <Order> orders;
public:
	Client(string name = "Anonymous", int clientNumber = 1, PromoCode promoCode = PromoCode())
		: name(name), clientNumber(clientNumber), promoCode(promoCode) {};
	bool isPromoCodeValid(const string& inputPromoCode);
	void addOrder(const Order& order);
	void removeOrder(int orderNumber);
	const vector<Order>& getOrders() const;
	bool checkClientOrder(Order& order);
	string getName() const;
	int getClientNumber() const;
	void printClientInfo() const;
};