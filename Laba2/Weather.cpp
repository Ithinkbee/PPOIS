#include "Weather.h"

double Weather::calculatePriceImpact(double basePrice) const {
    double priceFactor = 1.0;
    if (temperature < 0) {
        priceFactor += 0.2;
    }
    if (precipitation > 10.0) {
        priceFactor += 0.15;
    }
    if (windSpeed > 15.0) {
        priceFactor += 0.1;
    }
    return basePrice * priceFactor;
}
void Weather::printWeather() const {
    cout << "�����������: " << temperature << "�C" << endl;
    cout << "������: " << precipitation << " ��" << endl;
    cout << "�������� �����: " << windSpeed << " �/�" << endl;
}