#include <iostream>

//- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования);
template <typename ItemType>
Array<ItemType>::Array()
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
void Array<ItemType>::swap(Array& other) {
	std::swap(m_size, other->m_size);
	std::swap(m_array, other->m_array);
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

//- ввод/вывод в консоль (потоковый);
template <typename ItemType>
void Array<ItemType>::print() {
	std::cout << '[' << m_array[0];
	for (int i = 1; i < size; i++)
	{
		std::cout << ", " << m_array[i];
	}
	std::cout << ']' << std::endl;
}

//- сортировка элементов (любым алгоритмом);
template <typename ItemType>
void Array<ItemType>::qsort() {
    int i = 0;
    int j = m_size - 1;
    int mid = m_array[m_size / 2];
    do {
        while (m_array[i] < mid) {
            i++;
        }
        while (m_array[j] > mid) {
            j--;
        }
        if (i <= j) {
            int tmp = m_array[i];
            m_array[i] = m_array[j];
            m_array[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        qsort(m_array, j + 1);
    }
    if (i < size) {
        qsort(&m_array[i], m_size - i);
    }
}