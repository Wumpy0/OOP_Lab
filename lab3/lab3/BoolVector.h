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

	// Установка в 0 / 1 i - ой компоненты
	void set(size_t index);
	void reset(size_t index);

private:
	unsigned char* data;
	size_t bit_count;
private:
	size_t byte_count() const;
	void clear_tail();
	void check_index(size_t index) const;
};

// Вспомогательные методы
size_t BoolVector::byte_count() const {
	return (bit_count + 7) / 8;
}

void BoolVector::clear_tail() {
	size_t extra_bits = bit_count % 8;
	if (extra_bits != 0) {
		data[byte_count() - 1] &= (0xFF >> (8 - extra_bits));
	}
}

void BoolVector::check_index(size_t index) const {
	assert(index < bit_count);
}

// Конструкторы:

// По умолчанию
BoolVector::BoolVector() : data(nullptr), bit_count(0) {}
// С параметрами (размер и значение - одно и то же для всех разрядов)
BoolVector::BoolVector(size_t size, bool value) : bit_count(size) {
	size_t bytes = byte_count();
	data = new unsigned char[bytes];
	memset(data, value ? 0xFF : 0x00, bytes);
	clear_tail();
}
// Конструктор из массива const char *
BoolVector::BoolVector(const char* str) {
	bit_count = strlen(str);
	size_t bytes = byte_count();
	data = new unsigned char[bytes];

	for (size_t i = 0; i < bit_count; ++i) {
		if (str[i] == '1') {
			set(i);
		}
		else {
			assert(str[i] == '0');
		}
	}
}
// Конструктор копирования
BoolVector::BoolVector(const BoolVector& other) : bit_count(other.bit_count) {
	size_t bytes = byte_count();
	data = new unsigned char[bytes];
	memcpy(data, other.data, bytes);
}
// Деструктор
BoolVector::~BoolVector() {
	delete[] data;
}

// Установка в 0 / 1 i - ой компоненты
void BoolVector::set(size_t index) {
	check_index(index);
	data[index / 8] |= (1 << (index % 8));
}

void BoolVector::reset(size_t index) {
	check_index(index);
	data[index / 8] &= ~(1 << (index % 8));
}