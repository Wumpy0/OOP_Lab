#pragma once

#include <iostream>
#include <cstring>
#include <cassert>

class BoolVector
{
private:
	class Rank {
	public:
		Rank(unsigned char* byte_ptr, size_t bit);
		operator bool() const;
		Rank& operator=(bool value);
	private:
		unsigned char* byte;
		size_t bit;
	};
public:
	// ������������
	BoolVector();
	BoolVector(size_t size, bool value);
	BoolVector(const char* str);
	BoolVector(const BoolVector& other);
	~BoolVector();

	// ��������� � 0/1 i - �� ����������
	void set(size_t index);
	void reset(size_t index);
	// ��������� � 0/1 k ���������, ������� � i-��
	void setValue(size_t index, bool value, size_t count = 1);
	// ��������� � 0/1 ���� ��������� �������
	void setAll(bool value);
	// ����� (���������� ���) �������
	size_t length() const;
	// ��� ������� (���������� ��������� ���������)
	size_t weight() const;
	// ���� / ����� � �������(���������)
	friend std::ostream& operator<<(std::ostream& os, const BoolVector& bv);
	friend std::istream& operator>>(std::istream& is, BoolVector& bv);
	// ����� ����������� � ������ �������� (swap)
	void swap(BoolVector& other);
	// �������� ���� ��������� �������
	void invert();
	// �������� i-�� ����������
	void invert(size_t index);
	// ��������� ����������([])
	Rank operator[](size_t index);
	bool operator[](size_t index) const;
	// ��������� ���������(&=)
	BoolVector& operator&=(const BoolVector& rvalue);
	// ��������� ��������(|=)
	BoolVector& operator|=(const BoolVector& rvalue);
	// ��������� ����������� ���(^=)
	BoolVector& operator^=(const BoolVector& rhs);
	// ��������� ������(<<=, >>=)
	BoolVector& operator<<=(size_t shift);
	BoolVector& operator>>=(size_t shift);
	// ��������� ��������(~)
	BoolVector operator~() const;
	// ������������(=)
	BoolVector& operator=(const BoolVector& rvalue);
private:
	unsigned char* data;
	size_t bit_count;
private:
	// ��������������� ������
	size_t byteCount() const;
	void clearTail();
	void checkIndex(size_t index) const;
	void checkSize(const BoolVector& other) const;
};
// ������� ���������� ��������� (&, |, ^, <<, >>)
BoolVector operator&(const BoolVector& lvalue, const BoolVector& rvalue);
BoolVector operator|(const BoolVector& lvalue, const BoolVector& rvalue);
BoolVector operator^(const BoolVector& lvalue, const BoolVector& rvalue);
BoolVector operator<<(const BoolVector& bv, size_t shift);
BoolVector operator>>(const BoolVector& bv, size_t shift);