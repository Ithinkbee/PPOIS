#include "pch.h"
#include "../PPOISlaba2/Order.h"
#include "../PPOISlaba2/Order.cpp"

TEST(OrderTest, DefaultConstructor) {
    Order order;
    EXPECT_EQ(order.getNumber(), 1);
    EXPECT_DOUBLE_EQ(order.getCost(), 10.0);
    EXPECT_EQ(order.getDistance(), 1);
    EXPECT_EQ(order.getVehicle(), "Не указан");
    EXPECT_EQ(order.getPayment().getMethod(), PaymentMethod::Cash);
    EXPECT_DOUBLE_EQ(order.getPayment().getAmount(), 0.0);
}

TEST(OrderTest, ParameterizedConstructor) {
    Payment payment(PaymentMethod::Card, 150.0);
    Order order(42, 200.0, 15, "Автомобиль", payment);

    EXPECT_EQ(order.getNumber(), 42);
    EXPECT_DOUBLE_EQ(order.getCost(), 200.0);
    EXPECT_EQ(order.getDistance(), 15);
    EXPECT_EQ(order.getVehicle(), "Автомобиль");
    EXPECT_EQ(order.getPayment().getMethod(), PaymentMethod::Card);
    EXPECT_DOUBLE_EQ(order.getPayment().getAmount(), 150.0);
}

TEST(OrderTest, EqualityOperator) {
    Payment payment(PaymentMethod::Online, 300.0);
    Order order1(10, 500.0, 20, "Мотоцикл", payment);
    Order order2(10, 500.0, 20, "Мотоцикл", payment);

    EXPECT_TRUE(order1 == order2);

    Order order3(11, 400.0, 15, "Микроавтобус", payment);
    EXPECT_FALSE(order1 == order3);
}

TEST(OrderTest, SetNumber) {
    Order order;
    order.setNumber(99);
    EXPECT_EQ(order.getNumber(), 99);
}

TEST(OrderTest, SetVehicle) {
    Order order;
    order.setVehicle("Мотоцикл");
    EXPECT_EQ(order.getVehicle(), "Мотоцикл");

    ostringstream output;
    streambuf* oldCout = cout.rdbuf(output.rdbuf());
    order.setVehicle("");
    cout.rdbuf(oldCout);

    EXPECT_EQ(output.str(), "Ошибка: тип транспорта не может быть пустым!\n");
    EXPECT_EQ(order.getVehicle(), "Мотоцикл");
}

TEST(OrderTest, SetPayment) {
    Payment payment(PaymentMethod::Online, 250.0);
    Order order;
    order.setPayment(payment);

    EXPECT_EQ(order.getPayment().getMethod(), PaymentMethod::Online);
    EXPECT_DOUBLE_EQ(order.getPayment().getAmount(), 250.0);
}

TEST(OrderTest, PrintInfoOutput) {
    setlocale(LC_ALL, "Russian");
    Payment payment(PaymentMethod::Cash, 500);

    Order order(1, 500.0, 10.0, "Легковой автомобиль", payment);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    order.printInfo();

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
        "----------------------------------------\n"
        "Информация о заказе:\n"
        "Номер заказа: 1\n"
        "Сумма заказа: 500 руб.\n"
        "Расстояние до клиента: 10 км.\n"
        "Тип доставки: Легковой автомобиль\n"
        "----------------------------------------\n"
        "Способ оплаты: Наличные\n"
        "Сумма: 500.00 руб.\n"
        "Оплачено сразу: Нет\n"
        "----------------------------------------\n";

    EXPECT_EQ(output.str(), expectedOutput);
}