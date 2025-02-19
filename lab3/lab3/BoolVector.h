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
	// Конструкторы
	BoolVector();
	BoolVector(size_t size, bool value);
	BoolVector(const char* str);
	BoolVector(const BoolVector& other);
	~BoolVector();

	// Установка в 0/1 i - ой компоненты
	void set(size_t index);
	void reset(size_t index);
	// Установка в 0/1 k компонент, начиная с i-ой
	void set_value(size_t index, bool value, size_t count = 1);
	// Установка в 0/1 всех компонент вектора
	void set_all(bool value);
	// Длина (количество бит) вектора
	size_t length() const;
	// Вес вектора (количество единичных компонент)
	
	// Ввод / вывод в консоль(потоковый)
	friend std::ostream& operator<<(std::ostream& os, const BoolVector& bv);
	friend std::istream& operator>>(std::istream& is, BoolVector& bv);
	
	// Обмен содержимого с другим вектором (swap)
	void swap(BoolVector& other);
	// Инверсия всех компонент вектора
	void invert();
	// Инверсия i-ой компоненты
	void invert(size_t index);

	// Получение компоненты([])
	Rank operator[](size_t index);
	bool operator[](size_t index) const;
	// Побитовое умножение(&=)
	BoolVector& operator&=(const BoolVector& rvalue);
	// Побитовое сложение(|=)
	BoolVector& operator|=(const BoolVector& rvalue);
	// Побитовое исключающее ИЛИ(^=)
	BoolVector& operator^=(const BoolVector& rhs);
	// Побитовые сдвиги(<<=, >>=)
	
	// Побитовая инверсия(~)
	BoolVector operator~() const;
	// Присваивание(=)
	BoolVector& operator=(const BoolVector& rvalue);
private:
	unsigned char* data;
	size_t bit_count;
private:
	// Вспомогательные методы
	size_t byte_count() const;
	void clear_tail();
	void check_index(size_t index) const;
	void check_size(const BoolVector& other) const;
};