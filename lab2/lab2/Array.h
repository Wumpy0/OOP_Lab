﻿#include <cassert>
#include <algorithm>
#include <iostream>

template <typename ItemType>
class Array {
public:
	typedef ItemType* pointer;
public:
	//- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования);
	Array(int size = 0);
	Array(ItemType* source, int size);
	Array(const Array& source);
	//- деструктор;
	~Array();
public:
	//- получение размера(количества хранимых элементов в настоящий момент);
	int size() const;
	//- обмен содержимого с другим массивом (swap);
	void swap(Array& other);
	//- поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
	int find(const ItemType& target) const;
	//- ввод/вывод в консоль (потоковый);
	void print() const;
	void scan();
	//- сортировка элементов (любым алгоритмом);
	void qsort();
	void sort();
	//- вставка элемента по индексу. Если индекс некорректный, вернуть false;
	bool insert(const ItemType& value, int index = - 1);
	//- удаление элемента по индексу. Если индекс некорректный, вернуть false;
	bool remove(int index = -1);
	//- удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false;
	bool removeFirstFound(ItemType& value);
	//- удаление всех элементов с заданным значением;
	void removeAll(ItemType& value);
	//- поиск максимального / минимального элемента;
	ItemType max() const;
	ItemType min() const;
	//- получение ссылки на элемент по индексу ([ ]);
	ItemType& operator[](int index);
	const ItemType& operator[](int index) const;
	//- присваивание(=);
	Array<ItemType>& operator=(const Array& other);
	Array<ItemType>& operator=(Array&& other);
	//- сравнение (== и !=);
	bool operator==(const Array& other);
	bool operator!=(const Array& other);
	//- сложение (конкатенация) с другим массивом(+ и +=);
	Array<ItemType> operator+(const Array& other) const;
	Array<ItemType>& operator+=(const Array& other);
	//- добавление элемента в конец массива (+ и +=);
	Array<ItemType> operator+(const ItemType& value) const;
	Array<ItemType>& operator+=(const ItemType& value);
	
public:
	class Iterator {
	public:
		Iterator();
		Iterator(pointer ptr);
		ItemType& operator*();
		Iterator& operator++();
		pointer getPointer() const;
		bool operator<(const Iterator& other) const;
		bool operator>(const Iterator& other) const;
		bool operator<=(const Iterator& other) const;
		bool operator>=(const Iterator& other) const;
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	private:
		pointer ptr;
	};
public:
	//- получение итераторов на начало/конец массива (методы должны называться begin и end. Метод end должен возвращать итератор не на последний элемент, а за позицию после него);
	Iterator begin();
	Iterator end();
	const Iterator begin() const;
	const Iterator end() const;
	//- вставка элемента перед итератором;
	void insert(const ItemType& value, const Iterator& it);
	//- удаление элемента или диапазона элементов с помощью итераторов;
	void remove(Iterator first, Iterator last = Iterator());
private:
	void quickSortArr(ItemType* array, int size);
	ItemType* m_array = nullptr;
	int m_size = 0;
};

template <typename ItemType>
Array<ItemType>::Array(int size)
{
	if (size < 0)
	{
		size = -size;
	}
	m_size = size;
	m_array = new ItemType[size];
	for (int i = 0; i < size; i++)
	{
		m_array[i] = ItemType(0);
	}
}

template <typename ItemType>
Array<ItemType>::Array(ItemType* source, int sizeOfSourse) {
	m_size = sizeOfSourse;
	m_array = new ItemType[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_array[i] = source[i];
	}
}
template <typename ItemType>
Array<ItemType>::Array(const Array& source) {
	m_size = source.m_size;
	m_array = new ItemType[m_size];
	for (int i = 0; i < source.m_size; i++)
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
void Array<ItemType>::swap(Array& other) {
	std::swap(m_size, other.m_size);
	std::swap(m_array, other.m_array);
}

//- поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
template <typename ItemType>
int Array<ItemType>::find(const ItemType& target) const {
	for (int i = 0; i < m_size; i++)
	{
		if (m_array[i] == target)
		{
			return i;
		}
	}
	return -1;
}

//- ввод/вывод в консоль (потоковый);
template <typename ItemType>
void Array<ItemType>::print() const {
	if (m_size == 0) {
		std::cout << "[]" << std::endl;
		return;
	}
	std::cout << '[' << m_array[0];
	for (int i = 1; i < m_size; i++)
	{
		std::cout << ", " << m_array[i];
	}
	std::cout << ']' << std::endl;
}
template <typename ItemType>
void Array<ItemType>::scan() {
	std::cout << "Input size: ";
	std::cin >> m_size;
	if (m_array) {
		delete[] m_array;
	}
	m_array = new ItemType[m_size];
	std::cout << "Input array:" << std::endl;
	for (int i = 0; i < m_size; i++)
	{
		std::cin >> m_array[i];
	}
}

//- сортировка элементов (любым алгоритмом);
template <typename ItemType>
void Array<ItemType>::sort() {
	std::sort(begin(), end());
}
template <typename ItemType>
void Array<ItemType>::qsort() {
	quickSortArr(m_array, m_size);
}
template <typename ItemType>
void Array<ItemType>::quickSortArr(ItemType* array, int size) {
	int i = 0;
	int j = size - 1;
	ItemType mid = array[size / 2];
	do {
		while (array[i] < mid) {
			i++;
		}
		while (array[j] > mid) {
			j--;
		}
		if (i <= j) {
			ItemType tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);

	if (j > 0) {
		quickSortArr(array, j + 1);
	}
	if (i < size) {
		quickSortArr(&array[i], size - i);
	}
}

//- вставка элемента по индексу. Если индекс некорректный, вернуть false;
template <typename ItemType>
bool Array<ItemType>::insert(const ItemType& value, int index) {
	if (index >= -1 && index <= m_size) {
		if (index == -1) {
			index = m_size;
		}
		m_size += 1;
		ItemType* tempArray = new ItemType[m_size];
		for (int i = 0; i < index; i++)
		{
			tempArray[i] = m_array[i];
		}
		tempArray[index] = value;
		for (int i = index + 1; i < m_size; i++)
		{
			tempArray[i] = m_array[i - 1];
		}
		delete[] m_array;
		m_array = tempArray;
		return true;
	}
	else {
		return false;
	}
}

//- удаление элемента по индексу. Если индекс некорректный, вернуть false;
template <typename ItemType>
bool Array<ItemType>::remove(int index) {
	if (index >= -1 && index < m_size) {
		m_size -= 1;
		if (index == -1) {
			index = m_size;
		}
		ItemType* tempArray = new ItemType[m_size];
		for (int i = 0; i < index; i++)
		{
			tempArray[i] = m_array[i];
		}
		for (int i = index; i < m_size; i++)
		{
			tempArray[i] = m_array[i + 1];
		}
		delete[] m_array;
		m_array = tempArray;
		return true;
	}
	else {
		return false;
	}
}

//- удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false;
template <typename ItemType>
bool Array<ItemType>::removeFirstFound(ItemType& value) {
	int index = this->find(value);
	if (index >= 0) {
		this->remove(index);
		return true;
	} 
	else {
		return false;
	}
}

//- удаление всех элементов с заданным значением;
template <typename ItemType>
void Array<ItemType>::removeAll(ItemType& value) {
	int index = this->find(value);
	while (index != -1)
	{
		this->remove(index);
		index = this->find(value);
	}
}

//- поиск максимального / минимального элемента;
template <typename ItemType>
ItemType Array<ItemType>::max() const {
	ItemType max = m_array[0];
	for (int i = 1; i < m_size; i++)
	{
		if (max < m_array[i]) {
			max = m_array[i];
		}
	}
	return max;
}
template <typename ItemType>
ItemType Array<ItemType>::min() const {
	ItemType min = m_array[0];
	for (int i = 1; i < m_size; i++)
	{
		if (min > m_array[i]) {
			min = m_array[i];
		}
	}
	return min;
}

//- получение ссылки на элемент по индексу ([]);
template <typename ItemType>
ItemType& Array<ItemType>::operator[](int index){
	//assert
	assert(index <= m_size);
	return m_array[index];
}
template <typename ItemType>
const ItemType& Array<ItemType>::operator[](int index) const {
	//assert
	assert(index <= m_size);
	return m_array[index];
}

//- присваивание(=);
template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array<ItemType>& other) {
	if (this != &other) {
		Array<ItemType> copy(other);
		swap(copy);
	}
	return *this;
}
template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(Array&& other) {
	swap(other);
	return *this;
}

//- сравнение (== и !=);
template <typename ItemType>
bool Array<ItemType>::operator==(const Array& other) {
	if (m_size != other.m_size) {
		return false;
	}
	for (int i = 0; i < m_size; i++)
	{
		if (m_array[i] != other.m_array[i]) {
			return false;
		}
	}
	return true;
}

template <typename ItemType>
bool Array<ItemType>::operator!=(const Array& other) {
	return !operator==(other);
}

//- сложение (конкатенация) с другим массивом(+ и +=);
template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const Array<ItemType>& other) const{
	Array tempArray(m_size + other.m_size);
	for (int i = 0; i < m_size; i++)
	{
		tempArray[i] = m_array[i];
	}
	for (int i = 0; i < other.m_size; i++)
	{
		tempArray[i + m_size] = other.m_array[i];
	}
	return tempArray;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const Array& other) {
	operator+(other).swap(*this);
	return *this;
}

// Переопределение оператора вывода <<
template <typename ItemType>
std::ostream& operator<<(std::ostream& os, const Array<ItemType>& array) {
	if (array.size() == 0) {
		os << "[]";
		return os;
	}
	os << '[' << array[0];
	for (int i = 1; i < array.size(); ++i) {
		os << ", " << array[i];
	}
	os << ']';
	return os;
}

// Переопределение оператора ввода >>
template <typename ItemType>
std::istream& operator>>(std::istream& is, Array<ItemType>& array) {
	array = Array<ItemType>(array.size());
	for (int i = 0; i < array.size(); ++i) {
		is >> array[i];
	}
	return is;
}

//- добавление элемента в конец массива (+ и +=);
template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const ItemType& value) const {
	Array tempArray(*this);
	tempArray.insert(value);
	return tempArray;
}
template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const ItemType& value) {
	operator+(value).swap(*this);
	return *this;
}
//Iterator
template <typename ItemType>	
Array<ItemType>::Iterator::Iterator() {
	ptr = nullptr;
}
template <typename ItemType>
Array<ItemType>::Iterator::Iterator(pointer ptr) 
	: ptr(ptr) {}
template <typename ItemType>
ItemType& Array<ItemType>::Iterator::operator*() {
	return *ptr;
}
template <typename ItemType>
typename Array<ItemType>::Iterator& Array<ItemType>::Iterator::operator++() {
	++ptr;
	return *this;
}
template <typename ItemType>
typename Array<ItemType>::pointer Array<ItemType>::Iterator::getPointer() const {
	return ptr;
}

template <typename ItemType>
bool Array<ItemType>::Iterator::operator<(const Iterator& other) const {
	return ptr < other.ptr;
}
template <typename ItemType>
bool Array<ItemType>::Iterator::operator>(const Iterator& other) const {
	return ptr > other.ptr;
}
template <typename ItemType>
bool Array<ItemType>::Iterator::operator<=(const Iterator& other) const {
	return ptr <= other.ptr;
}
template <typename ItemType>
bool Array<ItemType>::Iterator::operator>=(const Iterator& other) const {
	return ptr >= other.ptr;
}
template <typename ItemType>
bool Array<ItemType>::Iterator::operator==(const Iterator& other) const {
	return ptr == other.ptr;
}
template <typename ItemType>
bool Array<ItemType>::Iterator::operator!=(const Iterator& other) const {
	return !operator==(other);
}
//- получение итераторов на начало/конец массива (методы должны называться begin и end. Метод end должен возвращать итератор не на последний элемент, а за позицию после него);
template <typename ItemType>
typename Array<ItemType>::Iterator Array<ItemType>::begin() {
	return m_array;
}
template <typename ItemType>
typename Array<ItemType>::Iterator Array<ItemType>::end() {
	return m_array + m_size;
}
template <typename ItemType>
const typename Array<ItemType>::Iterator Array<ItemType>::begin() const {
	return m_array;
}
template <typename ItemType>
const typename Array<ItemType>::Iterator Array<ItemType>::end() const {
	return m_array + m_size;
}
//- вставка элемента перед итератором;
template <typename ItemType>
void Array<ItemType>::insert(const ItemType& value, const Iterator& it) {
	assert(it >= begin() && it <= end());
	insert(value, it.getPointer() - m_array);
}
//- удаление элемента или диапазона элементов с помощью итераторов;
template <typename ItemType>
void Array<ItemType>::remove(Iterator first, Iterator last) {
	assert(first >= end() || first <= begin() || last >= end() || last <= begin() || first < last);
	int startIndex = first.getPointer() - m_array; 
	int endIndex;
	if (last == Iterator()) {
		endIndex = startIndex + 1;
	}
	else {
		endIndex = last.getPointer() - m_array;
	}
	ItemType* TempArray = new ItemType[m_size - (endIndex - startIndex)];
	for (int i = 0; i < startIndex; ++i) {
		TempArray[i] = m_array[i];
	}
	for (int i = endIndex; i < m_size; ++i) {
		TempArray[startIndex + (i - endIndex)] = m_array[i];
	}
	delete[] m_array;
	m_array = TempArray;
	m_size = m_size - (endIndex - startIndex);
}