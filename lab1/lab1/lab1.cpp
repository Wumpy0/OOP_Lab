#include <iostream>

using namespace std;

class Fraction {
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
public:
	//- конструктор (по умолчанию + как минимум один конструктор с параметрами);
	Fraction() : numerator(0), denominator(1) { }
	Fraction(int a) : numerator(0), denominator(1) {
		numerator = a;
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
	bool set_value(int a, int b) {
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
	void set_numerator(int a) {
		numerator = a;
	}
	bool set_denominator(int a) {
		if (a != 0) {
			denominator = a;
			return 1;
		}
		else {
			cerr << "Denominator may not be 0." << endl;
			return 0;
		}
	}
	void get_value(int& a, int& b) {
		a = numerator;
		b = denominator;
	}
	void get_denominator(int& a) {
		a = denominator;
	}
	void get_numerator(int& a) {
		a = numerator;
	}
	//- ввод/вывод дроби в консоль;
	void input() {
		cout << "Input Fraction:" << endl;
		cin >> this->numerator >> this->denominator;
	}
	void output() {
		cout << this->numerator << "/" << this->denominator;
	}
	//- приведение дроби к несократимой
	void shorten() {
		Fraction temp_f;
		int n = gcd(this->numerator, this->denominator);
		this->numerator /= n;
		this->denominator /= n;
	}
	//- арифметические операции между дробями(+, -, *, /)
	Fraction operator+(Fraction r) {
		Fraction temp_f;
		temp_f.set_value(this->numerator * r.denominator + r.numerator * this->denominator, this->denominator * r.denominator);
		return temp_f;
	}
	Fraction operator-(Fraction r) {
		Fraction temp_f;
		temp_f.set_value(this->numerator * r.denominator - r.numerator * this->denominator, this->denominator * r.denominator);
		return temp_f;
	}
	Fraction operator*(Fraction r) {
		Fraction temp_f;
		temp_f.set_value(this->numerator * r.numerator, this->denominator * r.denominator);
		return temp_f;
	}
	Fraction operator/(Fraction r) {
		Fraction temp_f;
		temp_f.set_value(this->numerator * r.denominator, this->denominator * r.numerator);
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
	double to_double() {
		double temp = double(this->numerator) / this->denominator;
		return temp;
	}
	//конвертация из десятичной в обыкновенную с точностью до 2-х знаков после запятой
	void to_Fraction(double a) {
		a *= 100;
		numerator = int(a);
		denominator = 100;
		this->shorten();
	}
};

int main()
{
	Fraction a;
	Fraction b(2);
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

	a.set_value(5, 12);
	b.set_denominator(3);
	c.set_numerator(7);
	cout << "a = ";
	a.output();
	cout << " (set_value(5, 12))" << endl;
	cout << "b = ";
	b.output();
	cout << " (set_denominator(3))" << endl;
	cout << "c = ";
	c.output();
	cout << " (set_numerator(7))" << endl;

	cout << "------------------" << endl;

	int a1, a2, b1, c2;
	a.get_value(a1, a2);
	b.get_numerator(b1);
	c.get_denominator(c2);
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
	x = a.to_double();
	cout << "a to double: " << x << endl;

	x = 1.755;
	d.to_Fraction(x);
	cout << "1.755 to Fraction .2: ";
	d.output();

	return 0;
}