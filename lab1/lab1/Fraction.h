#include <iostream>

class Fraction {
public:
	//- ����������� (�� ��������� + ��� ������� ���� ����������� � �����������);
	Fraction();
	Fraction(double a, int precision = 4);
	Fraction(int a, int b);
	//- ������������/��������� ���������/����������� �����;
	bool setValue(int a, int b);
	void setNumerator(int a);
	bool setDenominator(int a);
	void getValue(int& a, int& b) const;
	void getDenominator(int& a) const;
	void getNumerator(int& a) const;
	//- ����/����� ����� � �������;
	void input();
	void inputDouble();
	void output() const;
	//- ���������� ����� � ������������
	void shorten();
	//- �������������� �������� ����� �������(+, -, *, /)
	Fraction operator+(Fraction r) const;
	Fraction operator-(Fraction r) const;
	Fraction operator*(Fraction r) const;
	Fraction operator/(Fraction r) const;
	//- �������� ��������� (>, <, ==, !=)
	bool operator>(Fraction r) const;
	bool operator<(Fraction r) const;
	bool operator==(Fraction r) const;
	bool operator!=(Fraction r) const;
	//- ��� ������� ��� ���������� ����������� ������ �� ���� ����������
	//����������� �� ������������ ����� � ����������
	operator double() const;
	//��������� ����� �����
	operator int() const;
	//����������� �� ���������� � ������������ � ��������� �� 2-� ������ ����� �������
	void fromDouble(double a);

private:
	int numerator;   //���������
	int denominator; //�����������
	//���������� ����� �������� (Euklids algorithm)
	int gcd(int a, int b);
};