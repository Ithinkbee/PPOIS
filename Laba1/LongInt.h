#pragma once

#ifndef LONGINT_H
#define LONGINT_H

#include <vector>
#include <iostream>

class DInt {
private:
	void ignoreZeros();
	DInt digitMult(unsigned int digit) const;
	int digit(int index) const;
	std::vector<unsigned int> digits;
	bool sign;
public:
	DInt();
	DInt(std::string number);
	DInt(long long number);
	DInt(const DInt& rhs);
	DInt& operator=(const DInt& rhs);
	bool operator>(const DInt& rhs) const;
	bool operator<(const DInt& rhs) const;
	bool operator==(const DInt& rhs) const;
	bool operator>=(const DInt& rhs) const;
	bool operator<=(const DInt& rhs) const;
	bool operator!=(const DInt& rhs) const;
	const DInt operator+(const DInt& rhs) const;

	const DInt operator-(const DInt& rhs) const;
	const DInt operator*(const DInt& rhs) const;
	const DInt operator/(const DInt& rhs) const;
	DInt& operator+=(const DInt& rhs);
	DInt& operator-=(const DInt& rhs);
	DInt& operator*=(const DInt& rhs);
	DInt& operator/=(const DInt& rhs);
	DInt& operator++();
	DInt operator++(int);
	DInt& operator--();
	DInt operator--(int);
	std::string to_string() const;
	DInt abs() const;
};

#endif