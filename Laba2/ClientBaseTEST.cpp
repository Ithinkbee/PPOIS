#include "pch.h"
#include "../PPOISlaba2/ClientBase.h"
#include "../PPOISlaba2/ClientBase.cpp"

TEST(ClientBaseTest, Initialization) {
    PromoCode promo;
    ClientBase base(5, promo);

    EXPECT_EQ(base.getClientList().size(), 5);
    const auto& clients = base.getClientList();
    for (size_t i = 0; i < clients.size(); ++i) {
        EXPECT_EQ(clients[i].getName(), "Client" + to_string(i + 1));
    }
}

TEST(ClientBaseTest, AddClient) {
    ClientBase base(0); //пустая база
    PromoCode promo;

    base.addClient("NewClient", promo);
    EXPECT_EQ(base.getClientList().size(), 1); //клиент добавился?
    EXPECT_EQ(base.getClientList()[0].getName(), "NewClient");
}

TEST(ClientBaseTest, RemoveClient) {
    ClientBase base(3);

    int clientNumberToRemove = base.getClientList()[1].getClientNumber();
    base.removeClient(clientNumberToRemove);

    EXPECT_EQ(base.getClientList().size(), 2); 
    for (const auto& client : base.getClientList()) {
        EXPECT_NE(client.getClientNumber(), clientNumberToRemove); //клиент с этим номером отсутствует
    }
}

TEST(ClientBaseTest, CheckClientOrder) {
    PromoCode promo;
    ClientBase base(1, promo);
    auto& client = base.getClientList()[0];

    Order order1(1, 100.0, 10, "Car", Payment(PaymentMethod::Card, 100.0));
    Order order2(2, 200.0, 20, "Minibus", Payment(PaymentMethod::Cash, 200.0));
    client.addOrder(order1);

    EXPECT_TRUE(base.checkClientOrder(client.getClientNumber(), order1));
    EXPECT_FALSE(base.checkClientOrder(client.getClientNumber(), order2)); 
}

TEST(ClientBaseTest, RemoveNonExistentClient) {
    ClientBase base(2); 

    int nonExistentClientNumber = 9999;
    size_t originalSize = base.getClientList().size();
    base.removeClient(nonExistentClientNumber);

    EXPECT_EQ(base.getClientList().size(), originalSize); //размер не должен измениться
}

TEST(ClientBaseTest, EmptyBase) {
    ClientBase base(0);

    EXPECT_EQ(base.getClientList().size(), 0);
    Order dummyOrder;
    EXPECT_FALSE(base.checkClientOrder(1, dummyOrder));
}