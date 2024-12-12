#include "PromoCode.h"

const double PromoCode::MIN_DISCOUNT = 0.05;
const double PromoCode::MAX_DISCOUNT = 0.20;

PromoCode::PromoCode() {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    promoCode = "";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, chars.size() - 1);
    for (int i = 0; i < CODE_LENGTH; ++i) {
        promoCode += chars[dis(gen)];
    }
    uniform_real_distribution<> discountDis(MIN_DISCOUNT, MAX_DISCOUNT);
    discount = discountDis(gen);
}
void PromoCode::printPromoCodeInfo() const {
    cout << "Promo Code: " << promoCode << endl;
    cout << "Discount: " << discount * 100 << "%" << endl;
}
string PromoCode::getPromoCode() const { 
    return promoCode; 
}
double PromoCode::getDiscount() const {
    return discount; 
}
double PromoCode::applyDiscount(double price) const {
    return price * (1 - discount);
}