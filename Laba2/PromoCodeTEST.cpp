#include "pch.h"
#include "../PPOISlaba2/PromoCode.h"
#include "../PPOISlaba2/PromoCode.cpp"

TEST(PromoCodeTest, DefaultConstructor) {
    PromoCode promo;

    EXPECT_EQ(promo.getPromoCode().length(), 4);

    EXPECT_GE(promo.getDiscount(), 0.05);
    EXPECT_LE(promo.getDiscount(), 0.20);
}

TEST(PromoCodeTest, GetPromoCode) {
    PromoCode promo;
    string code = promo.getPromoCode();

    EXPECT_EQ(code.length(), 4);
    for (char c : code) {
        EXPECT_TRUE(isalnum(c)); //убедимся, что символы - буквы или цифры
    }
}

TEST(PromoCodeTest, GetDiscount) {
    PromoCode promo;
    double discount = promo.getDiscount();

    EXPECT_GE(discount, 0.05);
    EXPECT_LE(discount, 0.20);
}

TEST(PromoCodeTest, ApplyDiscount) {
    PromoCode promo;

    double originalPrice = 100.0;
    double discountedPrice = promo.applyDiscount(originalPrice);

    EXPECT_DOUBLE_EQ(discountedPrice, originalPrice * (1 - promo.getDiscount()));
}