#include <iostream>
#include "Fraction.h"

using namespace std;

//- ����������� (�� ��������� + ��� ������� ���� ����������� � �����������);
Fraction::Fraction()
	: Fraction(0, 1)
{ }
Fraction::Fraction(double a, int precision)
{
	if (precision < 0) {
		cerr << "Precision may not be < 0";
		precision = 1;
	}
	
	denominator = pow(10, precision);
	numerator = a * denominator;
	this->shorten();
}
Fraction::Fraction(int a, int b) : numerator(0), denominator(1) {
	if (b != 0) {
		numerator = a;
		denominator = b;
	}
	else {
		cerr << "Denominator may not be 0." << endl;
	}
}
//- ������������/��������� ���������/����������� �����;
bool Fraction::setValue(int a, int b) {
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
void Fraction::setNumerator(int a) {
	numerator = a;
}
bool Fraction::setDenominator(int a) {
	if (a != 0) {
		denominator = a;
		return 1;
	}
	else {
		cerr << "Denominator may not be 0." << endl;
		return 0;
	}
}
void Fraction::getValue(int& a, int& b) const {
	a = numerator;
	b = denominator;
}
void Fraction::getDenominator(int& a) const {
	a = denominator;
}
void Fraction::getNumerator(int& a) const {
	a = numerator;
}
//- ����/����� ����� � �������;
void Fraction::input() {
	cout << "Input Fraction:" << endl;
	cin >> numerator >> denominator;
}
void Fraction::inputDouble() {
	double temp;
	cout << "Enter the fraction in decimal format:" << endl;
	cin >> temp;
	this->fromDouble(temp);
}
void Fraction::output() const {
	cout << numerator << "/" << denominator;
}
//- ���������� ����� � ������������
void Fraction::shorten() {
	Fraction temp_f;
	int n = gcd(numerator, denominator);
	numerator /= n;
	denominator /= n;
}
//- �������������� �������� ����� �������(+, -, *, /)
Fraction Fraction::operator+(Fraction r) const {
	Fraction temp_f;
	temp_f.setValue(this->numerator * r.denominator + r.numerator * this->denominator, this->denominator * r.denominator);
	return temp_f;
}
Fraction Fraction::operator-(Fraction r) const {
	Fraction temp_f;
	temp_f.setValue(this->numerator * r.denominator - r.numerator * this->denominator, this->denominator * r.denominator);
	return temp_f;
}
Fraction Fraction::operator*(Fraction r) const {
	Fraction temp_f;
	temp_f.setValue(this->numerator * r.numerator, this->denominator * r.denominator);
	return temp_f;
}
Fraction Fraction::operator/(Fraction r) const {
	Fraction temp_f;
	temp_f.setValue(this->numerator * r.denominator, this->denominator * r.numerator);
	return temp_f;
}
//- �������� ��������� (>, <, ==, !=)
bool Fraction::operator>(Fraction r) const {
	int a = this->numerator * r.denominator;
	int b = r.numerator * this->denominator;
	return (a > b);
}
bool Fraction::operator<(Fraction r) const {
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
bool Fraction::operator==(Fraction r) const {
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
bool Fraction::operator!=(Fraction r) const {
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
//- ��� ������� ��� ���������� ����������� ������ �� ���� ����������
//����������� �� ������������ ����� � ����������
Fraction::operator double() const {
	double temp = double(numerator) / denominator;
	return temp;
}
//��������� ����� �����
Fraction::operator int() const {
	int temp = numerator / denominator;
	return temp;
}
//����������� �� ���������� � ������������ � ��������� �� 2-� ������ ����� �������
void Fraction::fromDouble(double a) {
	a *= 100;
	numerator = int(a);
	denominator = 100;
	this->shorten();
}
//���������� ����� �������� (Euklids algorithm)
int Fraction::gcd(int a, int b) {
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