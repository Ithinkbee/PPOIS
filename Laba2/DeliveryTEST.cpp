#include "pch.h"
#include "../PPOISlaba2/Delivery.h"
#include "../PPOISlaba2/Delivery.cpp"

TEST(DeliveryTest, ConstructorInitialization) {
    Bank bank;
    Weather weather(15.0, 5.0, 10.0);
    vector<Vehicle*> vehicles = { new Minibus(), new Car(), new Motorcycle() };

    Delivery delivery(vehicles, &bank, weather);

    ASSERT_EQ(vehicles.size(), 3);
}

TEST(DeliveryTest, AssignOrderSuccess) {
    Bank bank;
    Weather weather(15.0, 5.0, 10.0);
    vector<Vehicle*> vehicles = { new Minibus(), new Car(), new Motorcycle() };
    Delivery delivery(vehicles, &bank, weather);

    PromoCode promo;
    Order order(1, 1500.0, 15, "Не указан", Payment(PaymentMethod::Cash, 1500.0));

    bool result = delivery.assignOrder(order, promo);
    EXPECT_TRUE(result);
    EXPECT_NE(order.getVehicle(), "Не указан");
}

TEST(DeliveryTest, AssignOrderFailureNoVehicle) {
    Bank bank;
    Weather weather(-10.0, 20.0, 25.0); //плохие погодные условия
    vector<Vehicle*> vehicles = { new OnFoot(), new Bicycle() };
    Delivery delivery(vehicles, &bank, weather);

    PromoCode promo;
    Order order(1, 1500.0, 15, "Не указан", Payment(PaymentMethod::Cash, 1500.0));

    bool result = delivery.assignOrder(order, promo);
    EXPECT_FALSE(result);
    EXPECT_EQ(order.getVehicle(), "Не указан");
}

TEST(DeliveryTest, ProcessDeliverySuccess) {
    Bank bank;
    Weather weather(15.0, 5.0, 10.0);
    vector<Vehicle*> vehicles = { new Minibus(), new Car(), new Motorcycle() };
    Delivery delivery(vehicles, &bank, weather);

    PromoCode promo;
    Order order(1, 1500.0, 15, "Микроавтобус", Payment(PaymentMethod::Cash, 1500.0));
    delivery.assignOrder(order, promo);

    double deliveryTime = delivery.processDelivery();
    EXPECT_EQ(deliveryTime, 1); //дистанция 15 км / скорость 60 км/ч = 1 час (округление вверх)
}

TEST(DeliveryTest, ProcessDeliveryNoOrder) {
    Bank bank;
    Weather weather(15.0, 5.0, 10.0);
    vector<Vehicle*> vehicles = { new Minibus(), new Car(), new Motorcycle() };
    Delivery delivery(vehicles, &bank, weather);

    double deliveryTime = delivery.processDelivery();
    EXPECT_EQ(deliveryTime, 0); //без активного заказа
}

TEST(DeliveryTest, CompleteDeliverySuccess) {
    Bank bank;
    Weather weather(15.0, 5.0, 10.0);
    vector<Vehicle*> vehicles = { new Minibus(), new Car(), new Motorcycle() };
    Delivery delivery(vehicles, &bank, weather);

    PromoCode promo;
    Order order(1, 1500.0, 15, "Микроавтобус", Payment(PaymentMethod::Cash, 1500.0));
    delivery.assignOrder(order, promo);

    delivery.completeDelivery();
    EXPECT_GE(bank.getMoney(), 6200); //с максимальной скидкой
    EXPECT_LE(bank.getMoney(), 6425); //с минимальной скидкой
}