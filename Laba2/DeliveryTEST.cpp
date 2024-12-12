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
    Order order(1, 1500.0, 15, "�� ������", Payment(PaymentMethod::Cash, 1500.0));

    bool result = delivery.assignOrder(order, promo);
    EXPECT_TRUE(result);
    EXPECT_NE(order.getVehicle(), "�� ������");
}

TEST(DeliveryTest, AssignOrderFailureNoVehicle) {
    Bank bank;
    Weather weather(-10.0, 20.0, 25.0); //������ �������� �������
    vector<Vehicle*> vehicles = { new OnFoot(), new Bicycle() };
    Delivery delivery(vehicles, &bank, weather);

    PromoCode promo;
    Order order(1, 1500.0, 15, "�� ������", Payment(PaymentMethod::Cash, 1500.0));

    bool result = delivery.assignOrder(order, promo);
    EXPECT_FALSE(result);
    EXPECT_EQ(order.getVehicle(), "�� ������");
}

TEST(DeliveryTest, ProcessDeliverySuccess) {
    Bank bank;
    Weather weather(15.0, 5.0, 10.0);
    vector<Vehicle*> vehicles = { new Minibus(), new Car(), new Motorcycle() };
    Delivery delivery(vehicles, &bank, weather);

    PromoCode promo;
    Order order(1, 1500.0, 15, "������������", Payment(PaymentMethod::Cash, 1500.0));
    delivery.assignOrder(order, promo);

    double deliveryTime = delivery.processDelivery();
    EXPECT_EQ(deliveryTime, 1); //��������� 15 �� / �������� 60 ��/� = 1 ��� (���������� �����)
}

TEST(DeliveryTest, ProcessDeliveryNoOrder) {
    Bank bank;
    Weather weather(15.0, 5.0, 10.0);
    vector<Vehicle*> vehicles = { new Minibus(), new Car(), new Motorcycle() };
    Delivery delivery(vehicles, &bank, weather);

    double deliveryTime = delivery.processDelivery();
    EXPECT_EQ(deliveryTime, 0); //��� ��������� ������
}

TEST(DeliveryTest, CompleteDeliverySuccess) {
    Bank bank;
    Weather weather(15.0, 5.0, 10.0);
    vector<Vehicle*> vehicles = { new Minibus(), new Car(), new Motorcycle() };
    Delivery delivery(vehicles, &bank, weather);

    PromoCode promo;
    Order order(1, 1500.0, 15, "������������", Payment(PaymentMethod::Cash, 1500.0));
    delivery.assignOrder(order, promo);

    delivery.completeDelivery();
    EXPECT_GE(bank.getMoney(), 6200); //� ������������ �������
    EXPECT_LE(bank.getMoney(), 6425); //� ����������� �������
}