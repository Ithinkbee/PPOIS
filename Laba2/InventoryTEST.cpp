#include "pch.h"
#include "../PPOISlaba2/Inventory.h"
#include "../PPOISlaba2/Inventory.cpp"

TEST(InventoryDecreaseCount, ValidVehicleSuccess) {
    Inventory inventory(2, 1, 1, 1, 1);
    inventory.decreaseCount("����� ������");
    EXPECT_EQ(inventory.getAvailableCount("����� ������"), 1);
}

TEST(InventoryDecreaseCount, InsufficientVehicleFailure) {
    Inventory inventory(0, 1, 1, 1, 1);
    testing::internal::CaptureStdout();
    inventory.decreaseCount("����� ������");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "������: ������������ ������������ ������� ���� ����� ������\n");
    EXPECT_EQ(inventory.getAvailableCount("����� ������"), 0);
}

TEST(InventoryIncreaseCount, ValidVehicleSuccess) {
    Inventory inventory(1, 1, 1, 1, 1);
    inventory.increaseCount("����� ������");
    EXPECT_EQ(inventory.getAvailableCount("����� ������"), 2);
}

TEST(InventoryIncreaseCount, InvalidVehicleFailure) {
    Inventory inventory(1, 1, 1, 1, 1);
    testing::internal::CaptureStdout();
    inventory.increaseCount("�������");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "������: ������������ �������� ���� ������� �� �������.\n");
    EXPECT_EQ(inventory.getAvailableCount("�������"), 0);
}

TEST(InventoryGetAvailableCount, ValidVehicle) {
    Inventory inventory(2, 3, 4, 1, 5);
    EXPECT_EQ(inventory.getAvailableCount("������������"), 3);
}

TEST(InventoryGetAvailableCount, InvalidVehicle) {
    Inventory inventory(2, 3, 4, 1, 5);
    EXPECT_EQ(inventory.getAvailableCount("�������"), 0);
}
