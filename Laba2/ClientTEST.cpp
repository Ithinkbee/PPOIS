#include "pch.h"
#include "../PPOISlaba2/Client.h"
#include "../PPOISlaba2/Client.cpp"

TEST(ClientTest, DefaultConstructor) {
    Client client;
    EXPECT_EQ(client.getName(), "Anonymous");
    EXPECT_EQ(client.getClientNumber(), 1);
    EXPECT_FALSE(client.isPromoCodeValid("INVALID"));
}

TEST(ClientTest, ParameterizedConstructor) {
    PromoCode promo;
    Client client("John Doe", 42, promo);

    EXPECT_EQ(client.getName(), "John Doe");
    EXPECT_EQ(client.getClientNumber(), 42);
    EXPECT_FALSE(client.isPromoCodeValid("INVALID"));
}

TEST(ClientTest, IsPromoCodeValid) {
    PromoCode promo;
    Client client("Jane", 10, promo);

    EXPECT_TRUE(client.isPromoCodeValid(promo.getPromoCode()));  //валидный промокод
    EXPECT_FALSE(client.isPromoCodeValid("INVALID"));           //невалидный промокод
}

TEST(ClientTest, AddOrder) {
    Client client;
    Order order(1, 100.0, 5, "Car", Payment(PaymentMethod::Card, 100.0));
    client.addOrder(order);

    const auto& orders = client.getOrders();
    EXPECT_EQ(orders.size(), 1);
    EXPECT_EQ(orders[0].getNumber(), 1);
}

TEST(ClientTest, RemoveOrder) {
    Client client;
    Order order1(1, 100.0, 5, "Car", Payment(PaymentMethod::Card, 100.0));
    Order order2(2, 200.0, 10, "Motorcycle", Payment(PaymentMethod::Cash, 200.0));
    client.addOrder(order1);
    client.addOrder(order2);

    client.removeOrder(1);

    const auto& orders = client.getOrders();
    EXPECT_EQ(orders.size(), 1);
    EXPECT_EQ(orders[0].getNumber(), 2);
}

TEST(ClientTest, RemoveNonExistentOrder) {
    Client client;
    Order order(1, 100.0, 5, "Car", Payment(PaymentMethod::Card, 100.0));
    client.addOrder(order);

    client.removeOrder(999);  //удаляем заказ с несуществующим номером

    const auto& orders = client.getOrders();
    EXPECT_EQ(orders.size(), 1);
    EXPECT_EQ(orders[0].getNumber(), 1);
}

TEST(ClientTest, CheckClientOrder) {
    Client client;
    Order order1(1, 100.0, 5, "Car", Payment(PaymentMethod::Card, 100.0));
    Order order2(2, 200.0, 10, "Motorcycle", Payment(PaymentMethod::Cash, 200.0));
    client.addOrder(order1);

    EXPECT_TRUE(client.checkClientOrder(order1));  //существующий заказ
    EXPECT_FALSE(client.checkClientOrder(order2)); //несуществующий заказ
}