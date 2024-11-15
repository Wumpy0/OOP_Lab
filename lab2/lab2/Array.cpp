#include <iostream>
#include "Array.h"

template <typename ItemType>
//- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования);
Array<ItemType>::Array(int size)
	: m_array(nullptr), 
	m_size(0) 
{ }
template <typename ItemType>
Array<ItemType>::Array(const ItemType& source) {
	m_size = std::size(source);
	for (int i = 0; i < m_size; i++)
	{
		m_array[i] = source[i];
	}
}
template <typename ItemType>
Array<ItemType>::Array(const Array& source) {
	m_size = source.m_size;
	for (int i = 0; i < m_size; i++)
	{
		m_array[i] = source.m_array[i];
	}
}

//- деструктор;
template <typename ItemType>
Array<ItemType>::~Array() {
	delete[] m_array;
}

//- получение размера(количества хранимых элементов в настоящий момент);
template <typename ItemType>
int Array<ItemType>::size() const {
	return m_size;
}

//- обмен содержимого с другим массивом (swap);
template <typename ItemType>
void Array<ItemType>::swap(Array other) {
	std::swap(m_size, other.m_size);
	std::swap(m_array, other.m_array);
}

//- поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
template <typename ItemType>
int Array<ItemType>::find(ItemType target) const {
	for (int i = 0; i < m_size; i++)
	{
		if (m_array[i] == target) 
		{
			return i;
		}
	}
	return -1;
}