#include "pch.h"
#include "../PPOISlaba1/LongInt.h"
#include "../PPOISlaba1/LongInt.cpp"

// ���� ������������ �� ���������
TEST(ConstructorTEST, DefaultConstructor) {
    DInt a;
    EXPECT_EQ(a.to_string(), "0");
}

// ���� ������������ �� ������
TEST(ConstructorTEST, StringConstructor) {
    DInt a("12345");
    EXPECT_EQ(a.to_string(), "12345");

    DInt b("-98765");
    EXPECT_EQ(b.to_string(), "-98765");

    DInt c("000123");
    EXPECT_EQ(c.to_string(), "123");
}

// ���� ������������ �� �����
TEST(ConstructorTEST, NumberConstructor) {
    DInt a(12345);
    EXPECT_EQ(a.to_string(), "12345");

    DInt b(-98765);
    EXPECT_EQ(b.to_string(), "-98765");

    DInt c(0);
    EXPECT_EQ(c.to_string(), "0");
}

// ���� ��������� ��������
TEST(OperatorTEST, Addition) {
    DInt a("12345");
    DInt b("54321");
    EXPECT_EQ((a + b).to_string(), "66666");

    DInt c("-12345");
    EXPECT_EQ((a + c).to_string(), "0");

    DInt d("-54321");
    EXPECT_EQ((c + d).to_string(), "-66666");
}

// ���� ��������� ���������
TEST(OperatorTEST, Subtraction) {
    DInt a("54321");
    DInt b("12345");
    EXPECT_EQ((a - b).to_string(), "41976");

    DInt c("-12345");
    EXPECT_EQ((a - c).to_string(), "66666");
}

// ���� ��������� ���������
TEST(OperatorTEST, Multiplication) {
    DInt a("123");
    DInt b("456");
    EXPECT_EQ((a * b).to_string(), "56088");

    DInt c("-123");
    EXPECT_EQ((c * b).to_string(), "-56088");

    DInt d("-456");
    EXPECT_EQ((c * d).to_string(), "56088");
}

// ���� ��������� �������
TEST(OperatorTEST, Division) {
    DInt a("56088");
    DInt b("123");
    EXPECT_EQ((a / b).to_string(), "456");

    DInt c("-56088");
    EXPECT_EQ((c / b).to_string(), "-456");

    DInt d("-123");
    EXPECT_EQ((c / d).to_string(), "456");

    // ���� ������� �� 0 (������� ����������)
    EXPECT_THROW(a / DInt("0"), std::overflow_error);
}

// ���� ���������� ���������
TEST(OperatorTEST, Comparison) {
    DInt a("12345");
    DInt b("54321");
    DInt c("-12345");
    DInt d("12345");

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a >= d);
    EXPECT_TRUE(a <= d);
    EXPECT_TRUE(a == d);
    EXPECT_TRUE(a != c);
}

// ���� ������ abs()
TEST(MethodTEST, AbsoluteValue) {
    DInt a("-12345");
    EXPECT_EQ(a.abs().to_string(), "12345");

    DInt b("54321");
    EXPECT_EQ(b.abs().to_string(), "54321");

    DInt c("0");
    EXPECT_EQ(c.abs().to_string(), "0");
}

// ���� ���������� � ����������
TEST(OperatorTEST, IncrementDecrement) {
    DInt a("12345");
    EXPECT_EQ((++a).to_string(), "12346");
    EXPECT_EQ((a++).to_string(), "12346");
    EXPECT_EQ(a.to_string(), "12347");

    DInt b("-12345");
    EXPECT_EQ((--b).to_string(), "-12346");
    EXPECT_EQ((b--).to_string(), "-12346");
    EXPECT_EQ(b.to_string(), "-12347");
}

// ���� ������� ���������
TEST(OperatorTEST, ComplexExpressions) {
    DInt a("123");
    DInt b("456");
    DInt c("-789");

    EXPECT_EQ((a + a + a).to_string(), "369");
    EXPECT_EQ((a * b + c).to_string(), "55299");
}
