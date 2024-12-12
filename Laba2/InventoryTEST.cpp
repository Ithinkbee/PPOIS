#include "pch.h"
#include "../PPOISlaba2/Inventory.h"
#include "../PPOISlaba2/Inventory.cpp"

TEST(InventoryDecreaseCount, ValidVehicleSuccess) {
    Inventory inventory(2, 1, 1, 1, 1);
    inventory.decreaseCount("Пеший курьер");
    EXPECT_EQ(inventory.getAvailableCount("Пеший курьер"), 1);
}

TEST(InventoryDecreaseCount, InsufficientVehicleFailure) {
    Inventory inventory(0, 1, 1, 1, 1);
    testing::internal::CaptureStdout();
    inventory.decreaseCount("Пеший курьер");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Ошибка: Недостаточно транспортных средств типа Пеший курьер\n");
    EXPECT_EQ(inventory.getAvailableCount("Пеший курьер"), 0);
}

TEST(InventoryIncreaseCount, ValidVehicleSuccess) {
    Inventory inventory(1, 1, 1, 1, 1);
    inventory.increaseCount("Пеший курьер");
    EXPECT_EQ(inventory.getAvailableCount("Пеший курьер"), 2);
}

TEST(InventoryIncreaseCount, InvalidVehicleFailure) {
    Inventory inventory(1, 1, 1, 1, 1);
    testing::internal::CaptureStdout();
    inventory.increaseCount("Самокат");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Ошибка: Транспортное средство типа Самокат не найдено.\n");
    EXPECT_EQ(inventory.getAvailableCount("Самокат"), 0);
}

TEST(InventoryGetAvailableCount, ValidVehicle) {
    Inventory inventory(2, 3, 4, 1, 5);
    EXPECT_EQ(inventory.getAvailableCount("Микроавтобус"), 3);
}

TEST(InventoryGetAvailableCount, InvalidVehicle) {
    Inventory inventory(2, 3, 4, 1, 5);
    EXPECT_EQ(inventory.getAvailableCount("Самокат"), 0);
}
