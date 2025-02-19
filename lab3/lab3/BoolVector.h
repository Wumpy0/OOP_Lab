#pragma once

#include <iostream>
#include <cstring>
#include <cassert>

class BoolVector
{
public:
	class Rank {
	public:
		Rank();
		Rank(unsigned char* byte_ptr, size_t pos);
		~Rank();
		operator bool() const;
		Rank& operator=(bool value);
	private:
		unsigned char* byte;
		size_t bit_pos;
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
	void set_value(size_t index, bool value, size_t count = 1);
	// ��������� � 0/1 ���� ��������� �������
	void set_all(bool value);
	// ����� (���������� ���) �������
	size_t length() const;
	// ��� ������� (���������� ��������� ���������)
	
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
	
	// ��������� ��������(~)
	BoolVector operator~() const;
	// ������������(=)
	BoolVector& operator=(const BoolVector& rvalue);
private:
	unsigned char* data;
	size_t bit_count;
private:
	// ��������������� ������
	size_t byte_count() const;
	void clear_tail();
	void check_index(size_t index) const;
	void check_size(const BoolVector& other) const;
};