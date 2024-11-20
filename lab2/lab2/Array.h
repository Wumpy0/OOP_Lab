#include <iostream>

template <typename ItemType>
class Array {
public:
	//- ������������ (�� ���������, ����������� �� �������� �������, ����������� �����������);
	Array(int size = 0);
	Array(ItemType* source, int size);
	Array(const Array& source);
	//- ����������;
	~Array();

	//- ��������� �������(���������� �������� ��������� � ��������� ������);
	int size() const;
	//- ����� ����������� � ������ �������� (swap);
	void swap(Array& other);
	//- ����� �������� (���������� ������ ������� ���������� ��������, ���� -1, ���� ���������� ���);
	int find(ItemType target) const;
	//- ����/����� � ������� (���������);
	void print() const;
	void scan();
	//- ���������� ��������� (����� ����������);
	void qsort();
	//- ������� �������� �� �������. ���� ������ ������������, ������� false;
	bool insert(ItemType value, int index = - 1);
	//- �������� �������� �� �������. ���� ������ ������������, ������� false;
	bool remove(int index = -1);
	//- �������� �������� �� �������� (������ ���������). ���� ������� ����������� � �������, ������� false;
	bool removeFirstFound(ItemType value);
	//- �������� ���� ��������� � �������� ���������;
	void removeAll(ItemType value);
	//- ����� ������������� / ������������ ��������;
	int max() const;
	int min() const;
	//- ��������� ������ �� ������� �� ������� ([ ]);
	ItemType& operator[](int index) const;
	//- ������������(=);
	Array<ItemType>& operator=(const Array& other);
	//- ��������� (== � !=);
	bool operator==(const Array& other);
	bool operator!=(const Array& other);
	//- �������� (������������) � ������ ��������(+ � +=);
	const Array operator+(const Array& other);
	Array operator+=(const Array& other);
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
		m_array[i] = 0;
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
	for (int i = 0; i < m_size; i++)
	{
		m_array[i] = source.m_array[i];
	}
}

//- ����������;
template <typename ItemType>
Array<ItemType>::~Array() {
	delete[] m_array;
}

//- ��������� �������(���������� �������� ��������� � ��������� ������);
template <typename ItemType>
int Array<ItemType>::size() const {
	return m_size;
}

//- ����� ����������� � ������ �������� (swap);
template <typename ItemType>
void Array<ItemType>::swap(Array& other) {
	std::swap(m_size, other.m_size);
	std::swap(m_array, other.m_array);
}

//- ����� �������� (���������� ������ ������� ���������� ��������, ���� -1, ���� ���������� ���);
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

//- ����/����� � ������� (���������);
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

//- ���������� ��������� (����� ����������);
template <typename ItemType>
void Array<ItemType>::qsort() {
	quickSortArr(m_array, m_size);
}

template <typename ItemType>
void Array<ItemType>::quickSortArr(ItemType* array, int size) {
	int i = 0;
	int j = size - 1;
	int mid = array[size / 2];
	do {
		while (array[i] < mid) {
			i++;
		}
		while (array[j] > mid) {
			j--;
		}
		if (i <= j) {
			int tmp = array[i];
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

//- ������� �������� �� �������. ���� ������ ������������, ������� false;
template <typename ItemType>
bool Array<ItemType>::insert(ItemType value, int index) {
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

//- �������� �������� �� �������. ���� ������ ������������, ������� false;
template <typename ItemType>
bool Array<ItemType>::remove(int index) {
	if (index >= -1 && index <= m_size) {
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

//- �������� �������� �� �������� (������ ���������). ���� ������� ����������� � �������, ������� false;
template <typename ItemType>
bool Array<ItemType>::removeFirstFound(ItemType value) {
	int index = this->find(value);
	if (index >= 0) {
		this->remove(index);
		return true;
	} 
	else {
		return false;
	}
}

//- �������� ���� ��������� � �������� ���������;
template <typename ItemType>
void Array<ItemType>::removeAll(ItemType value) {
	int index = this->find(value);
	while (index != -1)
	{
		this->remove(index);
		index = this->find(value);
	}
}

//- ����� ������������� / ������������ ��������;
template <typename ItemType>
int Array<ItemType>::max() const {
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
int Array<ItemType>::min() const {
	ItemType min = m_array[0];
	for (int i = 1; i < m_size; i++)
	{
		if (min > m_array[i]) {
			min = m_array[i];
		}
	}
	return min;
}

//- ��������� ������ �� ������� �� ������� ([]);
template <typename ItemType>
ItemType& Array<ItemType>::operator[](int index) const {
	return m_array[index];
}

//- ������������(=);
template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array<ItemType>& other) {
	if (this != &other) {
		delete[] m_array;
		m_size = other.m_size;
		m_array = new ItemType[m_size];
		for (int i = 0; i < m_size; i++) {
			m_array[i] = other.m_array[i];
		}
	}
	return *this;
}

//- ��������� (== � !=);
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
	if (m_size != other.m_size) {
		return true;
	}
	for (int i = 0; i < m_size; i++)
	{
		if (m_array[i] != other.m_array[i]) {
			return true;
		}
	}
	return false;
}

//- �������� (������������) � ������ ��������(+ � +=);
template <typename ItemType>
 const Array<ItemType> Array<ItemType>::operator+(const Array<ItemType>& other) {
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
Array<ItemType> Array<ItemType>::operator+=(const Array<ItemType>& other) {
	ItemType* tempArray = new ItemType[m_size + other.m_size];
	for (int i = 0; i < m_size; i++)
	{
		tempArray[i] = m_array[i];
	}
	for (int i = 0; i < other.m_size; i++)
	{
		tempArray[i + m_size] = other.m_array[i];
	}
	m_size = m_size + other.m_size;
	delete[] m_array;
	m_array = tempArray;
	return *this;
}