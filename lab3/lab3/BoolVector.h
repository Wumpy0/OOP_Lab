#pragma once

#include <iostream>
#include <cstring>
#include <cassert>

class BoolVector
{
public:
	// ������������
	BoolVector();
	BoolVector(size_t size, bool value);
	BoolVector(const char* str);
	BoolVector(const BoolVector& other);
	~BoolVector();
public:
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
	
	// ����� ����������� � ������ �������� (swap)
	void swap(BoolVector& other);
	// �������� ���� ��������� �������
	void invert();
	// �������� i-�� ����������
	void invert(size_t index);

	//-��������� ����������([], ��.���������� ����);
	//-��������� ���������(&, &=);
	//-��������� ��������(| , |=);
	//-��������� ����������� ���(^, ^=);
	//-��������� ������(<< , >> , <<=, >>=);
	//-��������� ��������(~);
	//-������������(= ).
public:
	class Rank {

	};
private:
	unsigned char* data;
	size_t bit_count;
private:
	size_t byte_count() const;
	void clear_tail();
	void check_index(size_t index) const;
};