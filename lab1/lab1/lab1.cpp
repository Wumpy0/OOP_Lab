﻿#include <iostream>
#include "Fraction.h"

using namespace std;

/*
class Fraction {
public:
	//- конструктор (по умолчанию + как минимум один конструктор с параметрами);
	Fraction() : numerator(0), denominator(1) { }
	Fraction(double a) : numerator(0), denominator(10000) {
		a *= 10000;
		numerator = int(a);
		this->shorten();
	}
	Fraction(int a, int b) : numerator(0), denominator(1) {
		if (b != 0) {
			numerator = a;
			denominator = b;
		}
		else {
			cerr << "Denominator may not be 0." << endl;
		}
	}
	//- установление/получение числителя/знаменателя дроби;
	bool setValue(int a, int b) {
		if (b != 0) {
			numerator = a;
			denominator = b;
			return 1;
		}
		else {
			cerr << "Denominator may not be 0." << endl;
			return 0;
		}
	}
	void setNumerator(int a) {
		numerator = a;
	}
	bool setDenominator(int a) {
		if (a != 0) {
			denominator = a;
			return 1;
		}
		else {
			cerr << "Denominator may not be 0." << endl;
			return 0;
		}
	}
	void getValue(int& a, int& b) const {
		a = numerator;
		b = denominator;
	}
	void getDenominator(int& a) const {
		a = denominator;
	}
	void getNumerator(int& a) const {
		a = numerator;
	}
	//- ввод/вывод дроби в консоль;
	void input() {
		cout << "Input Fraction:" << endl;
		cin >> numerator >> denominator;
	}
	void inputDouble() {
		double temp;
		cout << "Enter the fraction in decimal format:" << endl;
		cin >> temp;
		this->toFraction(temp);
	}
	void output() const {
		cout << numerator << "/" << denominator;
	}
	//- приведение дроби к несократимой
	void shorten() {
		Fraction temp_f;
		int n = gcd(numerator, denominator);
		numerator /= n;
		denominator /= n;
	}
	//- арифметические операции между дробями(+, -, *, /)
	Fraction operator+(Fraction r) {
		Fraction temp_f;
		temp_f.setValue(this->numerator * r.denominator + r.numerator * this->denominator, this->denominator * r.denominator);
		return temp_f;
	}
	Fraction operator-(Fraction r) {
		Fraction temp_f;
		temp_f.setValue(this->numerator * r.denominator - r.numerator * this->denominator, this->denominator * r.denominator);
		return temp_f;
	}
	Fraction operator*(Fraction r) {
		Fraction temp_f;
		temp_f.setValue(this->numerator * r.numerator, this->denominator * r.denominator);
		return temp_f;
	}
	Fraction operator/(Fraction r) {
		Fraction temp_f;
		temp_f.setValue(this->numerator * r.denominator, this->denominator * r.numerator);
		return temp_f;
	}
	//- операции сравнения (>, <, ==, !=)
	bool operator>(Fraction r) {
		int a, b;
		a = this->numerator * r.denominator;
		b = r.numerator * this->denominator;
		if (a > b) {
			return 1;
		}
		else {
			return 0;
		}
	}
	bool operator<(Fraction r) {
		int a, b;
		a = this->numerator * r.denominator;
		b = r.numerator * this->denominator;
		if (a < b) {
			return 1;
		}
		else {
			return 0;
		}
	}
	bool operator==(Fraction r) {
		int a, b;
		a = this->numerator * r.denominator;
		b = r.numerator * this->denominator;
		if (a == b) {
			return 1;
		}
		else {
			return 0;
		}
	}
	bool operator!=(Fraction r) {
		int a, b;
		a = this->numerator * r.denominator;
		b = r.numerator * this->denominator;
		if (a != b) {
			return 1;
		}
		else {
			return 0;
		}
	}
	//- как минимум два уникальных собственных метода на ваше усмотрение
	//конвертация из обыкновенной дроби в десятичную
	operator double() const {
		double temp = double(numerator) / denominator;
		return temp;
	}
	//выделение целой части
	operator int() const {
		int temp = numerator / denominator;
		return temp;
	}
	//конвертация из десятичной в обыкновенную с точностью до 2-х знаков после запятой
	void toFraction(double a) {
		a *= 100;
		numerator = int(a);
		denominator = 100;
		this->shorten();
	}
private:
	int numerator;   //числитель
	int denominator; //знаменатель
	//наибольший общий делитель (Euklids algorithm)
	int gcd(int a, int b) {
		while (a != b) {
			if (a > b) {
				a -= b;
			}
			else {
				b -= a;
			}
		}
		return a;
	}
};
*/
int main()
{
	Fraction a;
	Fraction b(2.185, 2);
	Fraction c(3, 5);
	a.input();
	cout << "a = ";
	a.output();
	cout << endl;
	cout << "b = ";
	b.output();
	cout << endl;
	cout << "c = ";
	c.output();
	cout << endl;

	cout << "------------------" << endl;

	a.setValue(15, 12);
	b.setDenominator(3);
	c.setNumerator(7);
	cout << "a = ";
	a.output();
	cout << " (set value(5, 12))" << endl;
	cout << "b = ";
	b.output();
	cout << " (set denominator(3))" << endl;
	cout << "c = ";
	c.output();
	cout << " (set numerator(7))" << endl;

	cout << "------------------" << endl;

	int a1, a2, b1, c2;
	a.getValue(a1, a2);
	b.getNumerator(b1);
	c.getDenominator(c2);
	cout << "a value: " << a1 << ", " << a2 << endl;
	cout << "b numerator: " << b1 << endl;
	cout << "c denominator: " << c2 << endl;

	cout << "------------------" << endl;

	Fraction d;
	d = a + b;
	cout << "a + b = ";
	d.output();
	cout << endl;
	d = a - b;
	cout << "a - b = ";
	d.output();
	cout << endl;
	d = a * b;
	d.shorten();
	cout << "shorten a * b = ";
	d.output();
	cout << endl;
	d = a / b;
	d.shorten();
	cout << "shorten a / b = ";
	d.output();
	cout << endl;

	cout << "------------------" << endl;

	if (a > b) {
		cout << "a > b" << endl;
	}
	else
	{
		cout << "a not > b" << endl;
	}
	if (a < b) {
		cout << "a < b" << endl;
	}
	else
	{
		cout << "a not < b" << endl;
	}
	if (a == b) {
		cout << "a == b" << endl;
	}
	else
	{
		cout << "a not == b" << endl;
	}
	if (a != b) {
		cout << "a != b" << endl;
	}
	else
	{
		cout << "a not != b" << endl;
	}

	cout << "------------------" << endl;

	double x;
	x = double(a);
	cout << "a to double: " << x << endl;

	x = 1.755;
	d.fromDouble(x);
	cout << "1.755 to Fraction .2: ";
	d.output();
	cout << endl;

	int y;
	y = int(a);
	cout << "the whole part of a: " << y << endl;

	return 0;
}