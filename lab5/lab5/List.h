#pragma once

#include <iostream>
#include <cassert>

template <typename T>
class List {
public:
	// Конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования)
	List();
	List(const T* array, size_t arraySize);
	List(const List& other);
	// Деструктор
	~List();
	// Получение размера списка
	size_t getSize() const;
	// Обмен содержимого с другим списком (swap)
	void swap(List& other);
	// Ввод / вывод в консоль (потоковый)
	friend std::ostream& operator<<(std::ostream& os, const List<T>& list) {
		os << "[";
		Node* current = list.head_;
		while (current != nullptr) {
			os << current->data_;
			if (current->next_ != nullptr) {
				os << ", ";
			}
			current = current->next_;
		}
		os << "]";
		return os;
	}
	// Получение итераторов на начало / конец списка (методы должны называться begin и end. Метод end должен возвращать итератор не на последний элемент, а за позицию после него)
	// Поиск элемента по ключу (возвращает указатель / итератор на элемент или nullptr, если элемента нет в списке)
	// Добавление элемента в голову
	void push_front(const T& value);
	// Добавление элемента в хвост
	void push_back(const T& value);
	// Добавление элемента на позицию, после ключа (после первого вхождения), по итератору)
	// Удаление элемента из головы
	void pop_front();
	// Удаление элемента из хвоста
	void pop_back();
	// Удаление элемента из позиции, по ключу(первое вхождение), по итератору)
	// Удаление диапазона элементов с помощью итераторов
	// Поиск максимального / минимального элемента
	T max() const;
	T min() const;
	// IsEmpty() - возвращает true, если список пуст
	bool isEmpty() const;
	// Очистка списка
	void clear();
	// Сортировка списка

	// Присваивание (=)
	// Получение ссылки на ключ элемента ([])
	// Сравнение (==, !=)
	// Сложение (конкатенация) списков (+, +=)
public:
	class Iterator {};
	class ConstIterator {};
private:
	class Node {
	public:
		T data_;
		Node* previous_;
		Node* next_;
	public:
		Node(const T& value);
	};
private:
	Node* head_;
	Node* tail_;
	size_t size_;
};

// Конструкторы:
// По умолчанию
template <typename T>
List<T>::List() : head_(nullptr), tail_(nullptr), size_(0) {}

// Конструктор из обычного массива
template <typename T>
List<T>::List(const T* array, size_t arraySize) : head_(nullptr), tail_(nullptr), size_(0) {
	for (size_t i = 0; i < arraySize; ++i) {
		push_back(array[i]);
	}
}

// Конструктор копирования
template <typename T>
List<T>::List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
	Node* current = other.head_;
	while (current != nullptr) {
		push_back(current->data_);
		current = current->next_;
	}
}

// Деструктор
template <typename T>
List<T>::~List() {
	clear();
}

// Получение размера списка
template <typename T>
size_t List<T>::getSize() const { 
	return size_; 
}

// Обмен содержимого с другим списком (swap)
template <typename T>
void List<T>::swap(List& other) {
	std::swap(head_, other.head_);
	std::swap(tail_, other.tail_);
	std::swap(size_, other.size_);
}

// Ввод / вывод в консоль (потоковый)

// Добавление элемента в голову
template <typename T>
void List<T>::push_front(const T& value) {
	Node* newNode = new Node(value);
	if (head_ == nullptr) {
		tail_ = newNode;
		head_ = tail_;
	}
	else {
		newNode->next_ = head_;
		head_->previous_ = newNode;
		head_ = newNode;
	}
	size_++;
}

// Добавление элемента в хвост
template <typename T>
void List<T>::push_back(const T& value) {
	Node* newNode = new Node(value);
	if (tail_ == nullptr) {
		tail_ = newNode;
		head_ = tail_;
	}
	else {
		tail_->next_ = newNode;
		newNode->previous_ = tail_;
		tail_ = newNode;
	}
	size_++;
}

// Удаление элемента из головы
template <typename T>
void List<T>::pop_front() {
	if (head_ == nullptr) return;

	Node* temp = head_;
	head_ = head_->next_;
	if (head_ != nullptr) {
		head_->previous_ = nullptr;
	}
	else {
		tail_ = nullptr;
	}
	delete temp;
	size_--;
}
// Удаление элемента из хвоста
template <typename T>
void List<T>::pop_back() {
	if (tail_ == nullptr) return;

	Node* temp = tail_;
	tail_ = tail_->previous_;
	if (tail_ != nullptr) {
		tail_->next_ = nullptr;
	}
	else {
		head_ = nullptr;
	}
	delete temp;
	size_--;
}

// Поиск максимального / минимального элемента
template <typename T>
T List<T>::max() const {
	assert(!isEmpty());

	T maxVal = head_->data_;
	Node* current = head_->next_;
	while (current != nullptr) {
		if (current->data_ > maxVal) {
			maxVal = current->data_;
		}
		current = current->next_;
	}
	return maxVal;
}
template <typename T>
T List<T>::min() const {
	assert(!isEmpty());

	T minVal = head_->data_;
	Node* current = head_->next_;
	while (current != nullptr) {
		if (current->data_ < minVal) {
			minVal = current->data_;
		}
		current = current->next_;
	}
	return minVal;
}

// IsEmpty() - возвращает true, если список пуст
template <typename T>
bool List<T>::isEmpty() const {
	return size_ == 0; 
}

// Очистка списка
template <typename T>
void List<T>::clear() {
	while (head_ != nullptr) {
		Node* temp = head_;
		head_ = head_->next_;
		delete temp;
	}
	tail_ = nullptr;
	size_ = 0;
}

// Node
template <typename T>
List<T>::Node::Node(const T& value)
	: data_(value), previous_(nullptr), next_(nullptr) {}