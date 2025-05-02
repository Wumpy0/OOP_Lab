#pragma once

#include <iostream>
#include <cassert>

template <typename T>
class List {
public:
	class Iterator {
	public:
		friend class List<T>;
		Iterator(typename List<T>::Node* node = nullptr);
		T& operator*();
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	private:
		typename List<T>::Node* current_;
	};
	class ConstIterator {
	public:
		ConstIterator(const typename List<T>::Node* node = nullptr);
		const T& operator*() const;
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;
	private:
		const typename List<T>::Node* current_;
	};
public:
	// Конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования)
	List();
	List(const T* array, size_t arraySize);
	List(const List& other);
	// Деструктор
	~List();
	// Получение размера списка
	size_t size() const;
	// Обмен содержимого с другим списком (swap)
	void swap(List& other);
	// Ввод / вывод в консоль (потоковый)
	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const List<U>& list);
	template <typename U>
	friend std::istream& operator>>(std::istream& is, List<U>& list);
	// Получение итераторов на начало / конец списка (методы должны называться begin и end. Метод end должен возвращать итератор не на последний элемент, а за позицию после него)
	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	// Поиск элемента по ключу (возвращает указатель / итератор на элемент или nullptr, если элемента нет в списке)
	Iterator find(const T& key);
	ConstIterator find(const T& key) const;
	// Добавление элемента в голову
	void push_front(const T& value);
	// Добавление элемента в хвост
	void push_back(const T& value);
	// Добавление элемента на позицию
	void insert(size_t index, const T& value);
	// Добавление элемента после ключа(после первого вхождения), по итератору)
	void insertAfterKey(const T& key, const T& value);
	// Удаление элемента из головы
	void pop_front();
	// Удаление элемента из хвоста
	void pop_back();
	// Удаление элемента на позиции
	void remove(size_t index);
	// Удаление элемента по ключу(первое вхождение)
	void removeByKey(const T& key);
	// Удаление элемента по итератору
	void remove(const Iterator& it);
	// Удаление диапазона элементов с помощью итераторов
	void remove(const Iterator& first, const Iterator& last);
	// Поиск максимального / минимального элемента
	T max() const;
	T min() const;
	// IsEmpty() - возвращает true, если список пуст
	bool isEmpty() const;
	// Очистка списка
	void clear();
	// Сортировка списка
	void sort();
	// Присваивание (=)
	List& operator=(const List& other);
	// Получение ссылки на ключ элемента ([])
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	// Сравнение (==, !=)
	bool operator==(const List& other) const;
	bool operator!=(const List& other) const;
	// Сложение (конкатенация) списков (+, +=)
	List& operator+=(const List& other);
	List operator+(const List& other) const;
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
size_t List<T>::size() const { 
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
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
	os << "[";
	typename List<T>::Node* current = list.head_;
	if (current != nullptr) {
		os << current->data_;
		current = current->next_;
	}
	while (current != nullptr) {
		os << ", " << current->data_;
		current = current->next_;
	}
	os << "]";
	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, List<T>& list) {
	T value;
	while (is >> value) {
		list.push_back(value);
	}
	return is;
}

// Получение итераторов на начало / конец списка (методы должны называться begin и end. Метод end должен возвращать итератор не на последний элемент, а за позицию после него)
template <typename T>
typename List<T>::Iterator List<T>::begin() {
	return Iterator(head_);
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
	return Iterator(nullptr);
}

template <typename T>
typename List<T>::ConstIterator List<T>::begin() const {
	return ConstIterator(head_);
}

template <typename T>
typename List<T>::ConstIterator List<T>::end() const {
	return ConstIterator(nullptr);
}

// Поиск элемента по ключу (возвращает указатель / итератор на элемент или nullptr, если элемента нет в списке)
template <typename T>
typename List<T>::Iterator List<T>::find(const T& key) {
	Node* current = head_;
	while (current != nullptr) {
		if (current->data_ == key) {
			return Iterator(current);
		}
		current = current->next_;
	}
	return end();
}

template <typename T>
typename List<T>::ConstIterator List<T>::find(const T& key) const {
	const Node* current = head_;
	while (current != nullptr) {
		if (current->data_ == key) {
			return ConstIterator(current);
		}
		current = current->next_;
	}
	return end();
}

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

// Добавление элемента на позицию
template <typename T>
void List<T>::insert(size_t index, const T& value) {
	assert(index >= 0 && index <= size_);

	if (index == 0) {
		push_front(value);
	}
	else if (index == size_) {
		push_back(value);
	}
	else {
		Node* current = head_;
		for (size_t i = 0; i < index; ++i) {
			current = current->next_;
		}

		Node* newNode = new Node(value);
		newNode->previous_ = current->previous_;
		newNode->next_ = current;
		current->previous_->next_ = newNode;
		current->previous_ = newNode;
		size_++;
	}
}

// Добавление элемента после ключа(после первого вхождения), по итератору)
template <typename T>
void List<T>::insertAfterKey(const T& key, const T& value) {
	Node* current = head_;
	size_t index = 0;
	while (current && current->data_ != key) {
		current = current->next_;
		++index;
	}
	if (current) {
		insert(++index, value);
	}
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

// Удаление элемента на позиции
template <typename T>
void List<T>::remove(size_t index) {
	assert(index < size_);

	if (index == 0) {
		pop_front();
	}
	else if (index == size_ - 1) {
		pop_back();
	}
	else {
		Node* current = head_;
		for (size_t i = 0; i < index; ++i) {
			current = current->next_;
		}

		current->previous_->next_ = current->next_;
		current->next_->previous_ = current->previous_;
		delete current;
		size_--;
	}
}

// Удаление элемента по ключу(первое вхождение)
template <typename T>
void List<T>::removeByKey(const T& key) {
	Iterator it = this->find(key);
	remove(it);
}

// Удаление элемента по итератору
template <typename T>
void List<T>::remove(const Iterator& it) {
	if (it == end()) {
		return;
	}

	Node* current = it.current_;
	if (current == head_) {
		pop_front();
	}
	else if (current == tail_) {
		pop_back();
	}
	else {
		current->previous_->next_ = current->next_;
		current->next_->previous_ = current->previous_;
		delete current;
		size_--;
	}
}

// Удаление диапазона элементов с помощью итераторов
template <typename T>
void List<T>::remove(const Iterator& first, const Iterator& last) {
	if (first == last) {
		return;
	}

	Iterator current = first;

	while (current != end() && current != last) {
		remove(current++);
	}

	if (current == end() && last != end()) {
		current = begin();
		while (current != last) {
			remove(current++);
		}
	}
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

// Сортировка списка
template <typename T>
void List<T>::sort() {
	if (size_ < 2) return;

	bool swapped;
	do {
		swapped = false;
		Node* current = head_;
		while (current->next_) {
			if (current->data_ > current->next_->data_) {
				std::swap(current->data_, current->next_->data_);
				swapped = true;
			}
			current = current->next_;
		}
	} while (swapped);
}

// Присваивание (=)
template <typename T>
List<T>& List<T>::operator=(const List& other) {
	if (this != &other) {
		clear();
		Node* current = other.head_;
		while (current != nullptr) {
			push_back(current->data_);
			current = current->next_;
		}
	}
	return *this;
}

// Получение ссылки на ключ элемента ([])
template <typename T>
T& List<T>::operator[](size_t index) {
	assert(index <= size_);

	Node* current = head_;
	for (size_t i = 0; i < index; ++i) {
		current = current->next_;
	}
	return current->data_;
}

template <typename T>
const T& List<T>::operator[](size_t index) const {
	assert(index <= size_);

	Node* current = head_;
	for (size_t i = 0; i < index; ++i) {
		current = current->next_;
	}
	return current->data_;
}

// Сравнение
template <typename T>
bool List<T>::operator==(const List& other) const {
	if (size_ != other.size_) {
		return false;
	}

	Node* current1 = head_;
	Node* current2 = other.head_;
	while (current1 != nullptr) {
		if (current1->data_ != current2->data_) {
			return false;
		}
		current1 = current1->next_;
		current2 = current2->next_;
	}
	return true;
}

template <typename T>
bool List<T>::operator!=(const List& other) const {
	return !(*this == other);
}

// Сложение (конкатенация) списков (+, +=)
template <typename T>
List<T>& List<T>::operator+=(const List& other) {
	Node* current = other.head_;
	while (current != nullptr) {
		push_back(current->data_);
		current = current->next_;
	}
	return *this;
}

template <typename T>
List<T> List<T>::operator+(const List& other) const {
	List result = *this;
	result += other;
	return result;
}

// Iterator
template <typename T>
List<T>::Iterator::Iterator(typename List<T>::Node* node)
	: current_(node) {}

template <typename T>
T& List<T>::Iterator::operator*() {
	assert(current_ != nullptr);
	return current_->data_; 
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
	assert(current_ != nullptr);
	current_ = current_->next_;
	return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
	assert(current_ != nullptr);
	Iterator tmp = *this;
	current_ = current_->next_;
	return tmp;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
	assert(current_ != nullptr);
	current_ = current_->previous_;
	return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
	assert(current_ != nullptr);
	Iterator tmp = *this;
	current_ = current_->previous_;
	return tmp;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
	return current_ == other.current_;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
	return current_ != other.current_;
}

// ConstIterator
template <typename T>
List<T>::ConstIterator::ConstIterator(const typename List<T>::Node* node)
	: current_(node) {}

template <typename T>
const T& List<T>::ConstIterator::operator*() const {
	assert(current_ != nullptr);
	return current_->data_;
}

template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++() {
	assert(current_ != nullptr);
	current_ = current_->next_;
	return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) {
	assert(current_ != nullptr);
	ConstIterator tmp = *this;
	current_ = current_->next_;
	return tmp;
}

template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--() {
	assert(current_ != nullptr);
	current_ = current_->previous_;
	return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int) {
	assert(current_ != nullptr);
	ConstIterator tmp = *this;
	current_ = current_->previous_;
	return tmp;
}

template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& other) const {
	return current_ == other.current_;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const {
	return current_ != other.current_;
}

// Node
template <typename T>
List<T>::Node::Node(const T& value)
	: data_(value), previous_(nullptr), next_(nullptr) {}