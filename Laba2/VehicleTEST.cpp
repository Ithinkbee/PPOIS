#include "pch.h"
#include "../PPOISlaba2/Vehicle.h"
#include "../PPOISlaba2/Vehicle.cpp"
#include "../PPOISlaba2/Minibus.h"
#include "../PPOISlaba2/Car.h"
#include "../PPOISlaba2/Motorcycle.h"
#include "../PPOISlaba2/Bicycle.h"
#include "../PPOISlaba2/OnFoot.h"
#include <sstream>

TEST(VehicleTest, GetMethods) {
    Vehicle vehicle("Легковой автомобиль", 80.0, 200.0, 20.0);

    EXPECT_EQ(vehicle.getType(), "Легковой автомобиль");
    EXPECT_DOUBLE_EQ(vehicle.getCapacity(), 200.0);
    EXPECT_DOUBLE_EQ(vehicle.getRange(), 20.0);
    EXPECT_DOUBLE_EQ(vehicle.getSpeed(), 80.0);
}

TEST(MinibusTest, Initialization) {
    Minibus minibus;
    EXPECT_EQ(minibus.getType(), "Микроавтобус");
    EXPECT_DOUBLE_EQ(minibus.getSpeed(), 60);
    EXPECT_DOUBLE_EQ(minibus.getCapacity(), 5000);
    EXPECT_DOUBLE_EQ(minibus.getRange(), 20);
}

TEST(CarTest, Initialization) {
    Car car;
    EXPECT_EQ(car.getType(), "Легковой автомобиль");
    EXPECT_DOUBLE_EQ(car.getSpeed(), 75);
    EXPECT_DOUBLE_EQ(car.getCapacity(), 2000);
    EXPECT_DOUBLE_EQ(car.getRange(), 20);
}

TEST(MotorcycleTest, Initialization) {
    Motorcycle motorcycle;
    EXPECT_EQ(motorcycle.getType(), "Мотоцикл");
    EXPECT_DOUBLE_EQ(motorcycle.getSpeed(), 90);
    EXPECT_DOUBLE_EQ(motorcycle.getCapacity(), 700);
    EXPECT_DOUBLE_EQ(motorcycle.getRange(), 10);
}

TEST(BicycleTest, Initialization) {
    Bicycle bicycle;
    EXPECT_EQ(bicycle.getType(), "Велосипед");
    EXPECT_DOUBLE_EQ(bicycle.getSpeed(), 25);
    EXPECT_DOUBLE_EQ(bicycle.getCapacity(), 350);
    EXPECT_DOUBLE_EQ(bicycle.getRange(), 5);
}

TEST(OnFootTest, Initialization) {
    OnFoot onFoot;
    EXPECT_EQ(onFoot.getType(), "Пеший курьер");
    EXPECT_DOUBLE_EQ(onFoot.getSpeed(), 5);
    EXPECT_DOUBLE_EQ(onFoot.getCapacity(), 350);
    EXPECT_DOUBLE_EQ(onFoot.getRange(), 2);
}
