#pragma once

#ifndef LONGINT_H
#define LONGINT_H

#include <vector>
#include <iostream>

class LongInt {
private:
	void ignoreZeros();
	LongInt digitMult(unsigned int digit) const;
	int digit(int index) const;
	std::vector<unsigned int> digits;
	bool sign;
public:
	LongInt();
	LongInt(std::string number);
	LongInt(long long number);
	LongInt(const LongInt& rhs);
	LongInt& operator=(const LongInt& rhs);
	bool operator>(const LongInt& rhs) const;
	bool operator<(const LongInt& rhs) const;
	bool operator==(const LongInt& rhs) const;
	bool operator>=(const LongInt& rhs) const;
	bool operator<=(const LongInt& rhs) const;
	bool operator!=(const LongInt& rhs) const;
	const LongInt operator+(const LongInt& rhs) const;
	const LongInt operator-(const LongInt& rhs) const;
	const LongInt operator*(const LongInt& rhs) const;
	const LongInt operator/(const LongInt& rhs) const;
	LongInt& operator+=(const LongInt& rhs);
	LongInt& operator-=(const LongInt& rhs);
	LongInt& operator*=(const LongInt& rhs);
	LongInt& operator/=(const LongInt& rhs);
	LongInt& operator++();
	LongInt operator++(int);
	LongInt& operator--();
	LongInt operator--(int);
	std::string to_string() const;
	LongInt abs() const;
};

#endif
