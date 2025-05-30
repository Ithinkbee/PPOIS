#include "LongInt.h"
#include <algorithm>
#include <sstream>

LongInt::LongInt() {
	digits.push_back(0);
	sign = true;
}

LongInt::LongInt(std::string number) {
	int pos = isdigit(number.at(0)) ? 0 : 1;
	sign = number.at(0) == '-' ? false : true;
	for (unsigned int i = pos; i < number.length(); i++)
		digits.push_back(number.at(i) - '0');
	ignoreZeros();
}

LongInt::LongInt(long long number)
	: LongInt(std::to_string(number)) {
}

LongInt::LongInt(const LongInt& rhs) {
	sign = rhs.sign;
	digits = rhs.digits;
}

void LongInt::ignoreZeros() {
	while (digits.size() > 1 && digits.at(0) == 0)
		digits.erase(digits.begin(), digits.begin() + 1);
}

std::string LongInt::to_string() const {
	std::string str;
	if (!sign)
		str += "-";
	for (unsigned int i = 0; i < digits.size(); i++)
		str += std::to_string(digits.at(i));
	return str;
}

LongInt& LongInt::operator=(const LongInt& rhs) {
	if (this == &rhs)
		return *this;
	sign = rhs.sign;
	digits = rhs.digits;
	return *this;
}

bool LongInt::operator>(const LongInt& rhs) const {
	if (sign == true && rhs.sign == false)
		return true;
	if (sign == false && rhs.sign == true)
		return false;
	if (digits.size() > rhs.digits.size())
		return sign;
	if (digits.size() < rhs.digits.size())
		return !sign;

	for (size_t i = 0; i < digits.size(); i++) {
		if (digits.at(i) > rhs.digits.at(i))
			return sign;
		if (digits.at(i) < rhs.digits.at(i))
			return !sign;
	}
	return false;
}

bool LongInt::operator<(const LongInt& rhs) const {
	return false == (*this == rhs) && false == (*this > rhs);
}

bool LongInt::operator<=(const LongInt& rhs) const {
	return false == (*this > rhs);
}

bool LongInt::operator==(const LongInt& rhs) const {
	return (sign == rhs.sign && digits == rhs.digits);
}

bool LongInt::operator>=(const LongInt& rhs) const {
	return false == (*this < rhs);
}

bool LongInt::operator!=(const LongInt& rhs) const {
	return false == (*this == rhs);
}

LongInt LongInt::abs() const {
	LongInt a(*this);
	a.sign = true;
	return a;
}

int LongInt::digit(int index) const {
	return index >= 0 ? digits[index] : 0;
}

const LongInt LongInt::operator+(const LongInt& rhs) const {
	LongInt sum;
	if (digits.at(0) == 0 && rhs.digits.at(0) == 0)
		return sum;

	sum.digits.clear();
	sum.sign = sign;

	int carry = 0;
	int index1 = digits.size() - 1;
	int index2 = rhs.digits.size() - 1;

	while (index1 >= 0 || index2 >= 0) {
		int digit_sum = 0;

		if (index1 >= 0) {
			digit_sum += digit(index1);
			index1--;
		}
		if (index2 >= 0) {
			if (sign == rhs.sign) {
				digit_sum += rhs.digit(index2);
			}
			else {
				digit_sum -= rhs.digit(index2);
			}
			index2--;
		}
		digit_sum += carry;
		carry = digit_sum < 0 ? -1 : digit_sum / 10;
		digit_sum = (digit_sum + 10) % 10;
		sum.digits.insert(sum.digits.begin(), digit_sum);
	}

	if (carry != 0) {
		sum.digits.insert(sum.digits.begin(), carry);
	}
	while (sum.digits.size() > 1 && sum.digits.at(0) == 0) {
		sum.digits.erase(sum.digits.begin());
	}

	return sum;
}

const LongInt LongInt::operator-(const LongInt& rhs) const {
	LongInt neg_rhs = rhs;
	neg_rhs.sign = !neg_rhs.sign;

	LongInt diff = *this + neg_rhs;

	return diff;
}

LongInt LongInt::digitMult(unsigned int digit) const {
	LongInt result;
	result.digits.clear();
	result.sign = true;
	unsigned int carry = 0;
	for (int i = digits.size() - 1; i >= 0; i--) {
		unsigned int digitproduct = digits.at(i) * digit + carry;
		if (digitproduct > 9) {
			carry = digitproduct / 10;
			digitproduct %= 10;
		}
		else
			carry = 0;
		result.digits.push_back(digitproduct);
	}
	if (carry != 0)
		result.digits.push_back(carry);
	std::reverse(result.digits.begin(), result.digits.end());
	return result;
}

const LongInt LongInt::operator*(const LongInt& rhs) const {
	LongInt product;
	LongInt psum;
	unsigned int zeros_to_insert = 0;
	for (int i = rhs.digits.size() - 1; i >= 0; i--) {
		unsigned int digit = rhs.digits.at(i);
		product = this->digitMult(digit);
		product.digits.insert(product.digits.end(), zeros_to_insert++, 0);
		psum = psum + product;
	}
	if (sign != rhs.sign)
		psum.sign = false;
	return psum;
}

const LongInt LongInt::operator/(const LongInt& rhs) const {
	LongInt buffer;
	LongInt result;
	LongInt rhsAbs = rhs.abs();
	result.digits.clear();
	buffer.digits.clear();
	if (rhs == LongInt(0))
		throw std::overflow_error("Divide by zero exception");
	for (size_t i = 0; i < digits.size(); ++i) {
		buffer.digits.push_back(digits[i]);
		buffer.ignoreZeros();
		if (buffer < rhsAbs) {
			result.digits.push_back(0);
			continue;
		}
		int count;
		for (count = 0; buffer > rhsAbs || buffer == rhsAbs; ++count) {
			buffer = buffer - rhsAbs;
		}
		result.digits.push_back(count);
	}
	result.ignoreZeros();
	result.sign = true;
	if (sign != rhs.sign && result.digits[0] != 0)
		result.sign = false;
	return result;
}

LongInt& LongInt::operator+=(const LongInt& rhs) {
	*this = *this + rhs;
	return *this;
}

LongInt& LongInt::operator-=(const LongInt& rhs) {
	*this = *this - rhs;
	return *this;
}

LongInt& LongInt::operator*=(const LongInt& rhs) {
	*this = *this * rhs;
	return *this;
}

LongInt& LongInt::operator/=(const LongInt& rhs) {
	*this = *this / rhs;
	return *this;
}

LongInt& LongInt::operator++() {
	*this += LongInt(1);
	return *this;
}

LongInt LongInt::operator++(int)
{
	LongInt temp(*this);
	*this += LongInt(1);
	return temp;
}

LongInt& LongInt::operator--() {
	*this -= LongInt(1);
	return *this;
}

LongInt LongInt::operator--(int) {
	LongInt temp(*this);
	*this -= LongInt(1);
	return temp;
}
