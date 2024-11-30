#include "pch.h"
#include "../PPOISlaba1/LongInt.h"
#include "../PPOISlaba1/LongInt.cpp"

TEST(ConstructorTEST, DefaultConstructor) {
    LongInt a;
    EXPECT_EQ(a.to_string(), "0");
}

TEST(ConstructorTEST, StringConstructor) {
    LongInt a("12345");
    EXPECT_EQ(a.to_string(), "12345");

    LongInt b("-98765");
    EXPECT_EQ(b.to_string(), "-98765");

    LongInt c("000123");
    EXPECT_EQ(c.to_string(), "123");
}

TEST(ConstructorTEST, NumberConstructor) {
    LongInt a(12345);
    EXPECT_EQ(a.to_string(), "12345");

    LongInt b(-98765);
    EXPECT_EQ(b.to_string(), "-98765");

    LongInt c(0);
    EXPECT_EQ(c.to_string(), "0");
}

TEST(OperatorTEST, Addition) {
    LongInt a("12345");
    LongInt b("54321");
    EXPECT_EQ((a + b).to_string(), "66666");

    LongInt c("-12345");
    EXPECT_EQ((a + c).to_string(), "0");

    LongInt d("-54321");
    EXPECT_EQ((c + d).to_string(), "-66666");

    b += 5679;
    EXPECT_EQ((b).to_string(), "60000");

    EXPECT_EQ((a + 5).to_string(), "12350");

    LongInt e("100000000000000000000000000000000000000000000000000000000000000000000000");
    LongInt f("200000000000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ((e + f).to_string(), "300000000000000000000000000000000000000000000000000000000000000000000000");
}

TEST(OperatorTEST, Subtraction) {
    LongInt a("54321");
    LongInt b("12345");
    EXPECT_EQ((a - b).to_string(), "41976");

    LongInt c("-12345");
    EXPECT_EQ((a - c).to_string(), "66666");

    a -= 4321;
    EXPECT_EQ((a).to_string(), "50000");

    EXPECT_EQ((a - 1000).to_string(), "49000");

    LongInt e("100000000000000000000000000000000000000000000000000000000000000000000000");
    LongInt f("99999999999999999999999999999999999999999999999999999999999999999999999");
    EXPECT_EQ((e - f).to_string(), "1");
}

TEST(OperatorTEST, Multiplication) {
    LongInt a("123");
    LongInt b("456");
    EXPECT_EQ((a * b).to_string(), "56088");

    LongInt c("-123");
    EXPECT_EQ((c * b).to_string(), "-56088");

    LongInt d("-456");
    EXPECT_EQ((c * d).to_string(), "56088");

    c *= -3;
    EXPECT_EQ((c).to_string(), "369");

    EXPECT_EQ((a * 1000).to_string(), "123000");
}

TEST(OperatorTEST, Division) {
    LongInt a("56088");
    LongInt b("123");
    EXPECT_EQ((a / b).to_string(), "456");

    LongInt c("-56088");
    EXPECT_EQ((c / b).to_string(), "-456");

    LongInt d("-123");
    EXPECT_EQ((c / d).to_string(), "456");

    d /= d;
    EXPECT_EQ((d).to_string(), "1");

    EXPECT_EQ((b / 3).to_string(), "41");

    EXPECT_THROW(a / LongInt("0"), std::overflow_error);
}

TEST(OperatorTEST, Comparison) {
    LongInt a("12345");
    LongInt b("54321");
    LongInt c("-12345");
    LongInt d("12345");

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a >= d);
    EXPECT_TRUE(a <= d);
    EXPECT_TRUE(a == d);
    EXPECT_TRUE(a != c);
}

TEST(MethodTEST, AbsoluteValue) {
    LongInt a("-12345");
    EXPECT_EQ(a.abs().to_string(), "12345");

    LongInt b("54321");
    EXPECT_EQ(b.abs().to_string(), "54321");

    LongInt c("0");
    EXPECT_EQ(c.abs().to_string(), "0");
}

TEST(OperatorTEST, IncrementDecrement) {
    LongInt a("12345");
    EXPECT_EQ((++a).to_string(), "12346");
    EXPECT_EQ((a++).to_string(), "12346");
    EXPECT_EQ(a.to_string(), "12347");

    LongInt b("-12345");
    EXPECT_EQ((--b).to_string(), "-12346");
    EXPECT_EQ((b--).to_string(), "-12346");
    EXPECT_EQ(b.to_string(), "-12347");
}

TEST(OperatorTEST, ComplexExpressions) {
    LongInt a("123");
    LongInt b("456");
    LongInt c("-789");

    EXPECT_EQ((a + a + a).to_string(), "369");
    EXPECT_EQ((a * b + c).to_string(), "55299");
}
