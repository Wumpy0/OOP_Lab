#include <iostream>

class Fraction {
public:
	//- конструктор (по умолчанию + как минимум один конструктор с параметрами);
	Fraction();
	Fraction(double a, int precision = 4);
	Fraction(int a, int b);
	//- установление/получение числителя/знаменателя дроби;
	bool setValue(int a, int b);
	void setNumerator(int a);
	bool setDenominator(int a);
	void getValue(int& a, int& b) const;
	void getDenominator(int& a) const;
	void getNumerator(int& a) const;
	//- ввод/вывод дроби в консоль;
	void input();
	void inputDouble();
	void output() const;
	//- приведение дроби к несократимой
	void shorten();
	//- арифметические операции между дробями(+, -, *, /)
	Fraction operator+(Fraction r) const;
	Fraction operator-(Fraction r) const;
	Fraction operator*(Fraction r) const;
	Fraction operator/(Fraction r) const;
	//- операции сравнения (>, <, ==, !=)
	bool operator>(Fraction r) const;
	bool operator<(Fraction r) const;
	bool operator==(Fraction r) const;
	bool operator!=(Fraction r) const;
	//- как минимум два уникальных собственных метода на ваше усмотрение
	//конвертация из обыкновенной дроби в десятичную
	operator double() const;
	//выделение целой части
	operator int() const;
	//конвертация из десятичной в обыкновенную с точностью до 2-х знаков после запятой
	void fromDouble(double a);

private:
	int numerator;   //числитель
	int denominator; //знаменатель
	//наибольший общий делитель (Euklids algorithm)
	int gcd(int a, int b);
};