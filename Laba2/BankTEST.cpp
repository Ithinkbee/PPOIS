#include "pch.h"
#include "../PPOISlaba2/Bank.h"
#include "../PPOISlaba2/Bank.cpp"

TEST(BankTest, InitialMoney) {
    Bank bank;
    EXPECT_EQ(5000, bank.getMoney());
}

TEST(BankTest, AddMoney) {
    Bank bank;
    bank.addMoney(1000);
    EXPECT_EQ(6000, bank.getMoney());
}

TEST(BankTest, AddMoneyNegative) {
    Bank bank;
    testing::internal::CaptureStdout();
    bank.addMoney(-500);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Ошибка: сумма добавления должна быть положительной!\n", output);
    EXPECT_EQ(5000, bank.getMoney());
}