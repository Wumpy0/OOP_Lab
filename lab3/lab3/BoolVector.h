#pragma once

#include <iostream>
#include <cstring>
#include <cassert>

class BoolVector
{
public:
	// Конструкторы
	BoolVector();
	BoolVector(size_t size, bool value);
	BoolVector(const char* str);
	BoolVector(const BoolVector& other);
	~BoolVector();
public:
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
	
	// Обмен содержимого с другим вектором (swap)
	void swap(BoolVector& other);
	// Инверсия всех компонент вектора
	void invert();
	// Инверсия i-ой компоненты
	void invert(size_t index);

	//-получение компоненты([], см.примечание ниже);
	//-побитовое умножение(&, &=);
	//-побитовое сложение(| , |=);
	//-побитовое исключающее ИЛИ(^, ^=);
	//-побитовые сдвиги(<< , >> , <<=, >>=);
	//-побитовая инверсия(~);
	//-присваивание(= ).
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