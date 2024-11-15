#pragma once 

#include <iostream>

template <typename ItemType>
class Array {
public:
	//- ������������ (�� ���������, ����������� �� �������� �������, ����������� �����������);
	Array(int size = 10);
	Array(const ItemType& source);
	Array(const Array& source);
	//- ����������;
	~Array();
public:
	//- ��������� �������(���������� �������� ��������� � ��������� ������);
	int size() const;
	//- ����� ����������� � ������ �������� (swap);
	void swap(Array other);
	//- ����� �������� (���������� ������ ������� ���������� ��������, ���� -1, ���� ���������� ���);
	int find(ItemType target) const;
	//- ����/����� � ������� (���������);
private:
	ItemType* m_array = nullptr;
	int m_size = 0;
};