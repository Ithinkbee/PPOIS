#include "pch.h"
#include "../PPOISlaba2/Payment.h"
#include "../PPOISlaba2/Payment.cpp"
#include <sstream>

TEST(PaymentTest, DefaultConstructor) {
    Payment payment;
    EXPECT_EQ(payment.getMethod(), PaymentMethod::Cash);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 0.0);
    EXPECT_FALSE(payment.isPaidImmediately());
}

TEST(PaymentTest, ParameterizedConstructor) {
    Payment payment(PaymentMethod::Online, 100.0);
    EXPECT_EQ(payment.getMethod(), PaymentMethod::Online);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 100.0);
    EXPECT_TRUE(payment.isPaidImmediately());
}

TEST(PaymentTest, Getters) {
    Payment payment(PaymentMethod::Card, 200.0);
    EXPECT_EQ(payment.getMethod(), PaymentMethod::Card);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 200.0);
    EXPECT_FALSE(payment.isPaidImmediately());
}

TEST(PaymentTest, SetMethod) {
    Payment payment;
    payment.setMethod(PaymentMethod::Card);
    EXPECT_EQ(payment.getMethod(), PaymentMethod::Card);
}

TEST(PaymentTest, SetAmount) {
    Payment payment;
    payment.setAmount(150.0);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 150.0);

    ostringstream output;
    streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    payment.setAmount(-50.0);
    std::cout.rdbuf(oldCout);
    EXPECT_EQ(output.str(), "Ошибка: сумма оплаты не может быть отрицательной!\n");
    EXPECT_DOUBLE_EQ(payment.getAmount(), 150.0);
}

TEST(PaymentTest, SetPaidImmediately) {
    Payment payment;
    payment.setPaidImmediately(true);
    EXPECT_TRUE(payment.isPaidImmediately());
}

TEST(PaymentTest, PaymentMethodToString) {
    EXPECT_EQ(paymentMethodToString(PaymentMethod::Cash), "Наличные");
    EXPECT_EQ(paymentMethodToString(PaymentMethod::Card), "По карте");
    EXPECT_EQ(paymentMethodToString(PaymentMethod::Online), "Онлайн");
}