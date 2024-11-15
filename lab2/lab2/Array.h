#pragma once 

#include <iostream>

template <typename ItemType>
class Array {
public:
	//- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования);
	Array(int size = 10);
	Array(const ItemType& source);
	Array(const Array& source);
	//- деструктор;
	~Array();
public:
	//- получение размера(количества хранимых элементов в настоящий момент);
	int size() const;
	//- обмен содержимого с другим массивом (swap);
	void swap(Array other);
	//- поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
	int find(ItemType target) const;
	//- ввод/вывод в консоль (потоковый);
private:
	ItemType* m_array = nullptr;
	int m_size = 0;
};