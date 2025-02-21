#include "BoolVector.h"

// Rank
BoolVector::Rank::Rank(unsigned char* byte_ptr, size_t bit)
	: byte(byte_ptr), bit(bit) {};

BoolVector::Rank::operator bool() const {
	return (*byte >> bit) & 1;
}

BoolVector::Rank& BoolVector::Rank::operator=(bool value) {
	if (value) { 
		*byte |= (1 << bit);
	}
	else { 
		*byte &= ~(1 << bit);
	};
	return *this;
}

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

void BoolVector::check_size(const BoolVector& other) const {
	if (bit_count != other.bit_count)
		throw std::invalid_argument("Vector sizes mismatch");
}

// Конструкторы:

// По умолчанию
BoolVector::BoolVector() : 
	data(nullptr), 
	bit_count(0) {}
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
	data = new unsigned char[bytes] {};

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

// Длина (количество бит) вектора
size_t BoolVector::length() const {
	return bit_count;
}

// Вес вектора (количество единичных компонент)
size_t BoolVector::weight() const {
	size_t count = 0;
	for (size_t i = 0; i < bit_count; ++i) {
		if ((*this)[i]) {
			++count;
		}
	}
	return count;
}

// Получение компоненты([])
BoolVector::Rank BoolVector::operator[](size_t index) {
	check_index(index);
	return Rank(&data[index / 8], index % 8);
}

bool BoolVector::operator[](size_t index) const {
	check_index(index);
	return (data[index / 8] >> (index % 8)) & 1;
}

// Ввод/вывод
std::ostream& operator<<(std::ostream& os, const BoolVector& bv) {
	for (size_t i = 0; i < bv.bit_count; ++i)
		os << (bv[i] ? '1' : '0');
	return os;
}

std::istream& operator>>(std::istream& is, BoolVector& bv) {
	std::string s;
	is >> s;
	BoolVector temp(s.c_str());
	bv.swap(temp);
	return is;
}

// Обмен содержимого с другим вектором (swap)
void BoolVector::swap(BoolVector& other) {
	std::swap(data, other.data);
	std::swap(bit_count, other.bit_count);
}

// Инверсия всех компонент вектора
void BoolVector::invert() {
	size_t bytes = byte_count();
	for (size_t i = 0; i < bytes; ++i)
		data[i] = ~data[i];
	clear_tail();
}

// Инверсия i-ой компоненты
void BoolVector::invert(size_t index) {
	check_index(index);
	data[index / 8] ^= (1 << (index % 8));
}

// Установка в 0/1 k компонент, начиная с i-ой
void BoolVector::set_value(size_t index, bool value, size_t count) {
	check_index(index);
	assert(index + count <= bit_count);

	for (size_t i = index; i < index + count; ++i)
		value ? set(i) : reset(i);
}

// Установка в 0/1 всех компонент вектора
void BoolVector::set_all(bool value) {
	memset(data, value ? 0xFF : 0x00, byte_count());
	clear_tail();
}

// Побитовое умножение(&=)
BoolVector& BoolVector::operator&=(const BoolVector& rvalue) {
	check_size(rvalue);
	for (size_t i = 0; i < byte_count(); ++i)
		data[i] &= rvalue.data[i];
	return *this;
}

// Побитовое сложение(|=)
BoolVector& BoolVector::operator|=(const BoolVector& rvalue) {
	check_size(rvalue);
	for (size_t i = 0; i < byte_count(); ++i)
		data[i] |= rvalue.data[i];
	return *this;
}

// Побитовое исключающее ИЛИ(^=)
BoolVector& BoolVector::operator^=(const BoolVector& rvalue) {
	check_size(rvalue);
	for (size_t i = 0; i < byte_count(); ++i)
		data[i] ^= rvalue.data[i];
	return *this;
}

// Побитовые сдвиги(<<=, >>=)
BoolVector& BoolVector::operator<<=(size_t shift) {
	if (shift >= bit_count) {
		set_all(false);
		return *this;
	}

	size_t byte_shift = shift / 8;
	size_t bit_shift = shift % 8;
	size_t bytes = byte_count();
	if (byte_shift > 0) {
		for (size_t i = 0; i < bytes - byte_shift; ++i) {
			data[i] = data[i + byte_shift];
		}
		memset(data + bytes - byte_shift, 0, byte_shift);
	}
	
	if (bit_shift > 0) {
		for (size_t i = 0; i < bytes - 1; ++i) {
			data[i] = (data[i] >> bit_shift) | (data[i + 1] << (8 - bit_shift));
		}
		data[bytes - 1] <<= bit_shift;
	}

	clear_tail();
	return *this;
}

BoolVector& BoolVector::operator>>=(size_t shift) {
	if (shift >= bit_count) {
		set_all(false);
		return *this;
	}

	size_t byte_shift = shift / 8;
	size_t bit_shift = shift % 8;
	size_t bytes = byte_count();
	if (byte_shift > 0) {
		for (size_t i = bytes - 1; i >= byte_shift; --i) {
			data[i] = data[i - byte_shift];
		}
		memset(data, 0, byte_shift);
	}
	
	if (bit_shift > 0) {
		for (size_t i = bytes - 1; i > 0; --i) {
			data[i] = (data[i] << bit_shift) | (data[i - 1] >> (8 - bit_shift));
		}
		data[0] <<= bit_shift;
	}

	clear_tail();
	return *this;
}

// Побитовая инверсия(~)
BoolVector BoolVector::operator~() const {
	BoolVector result(*this);
	result.invert();
	return result;
}

// Присваивание(=)
BoolVector& BoolVector::operator=(const BoolVector& rvalue) {
	if (this != &rvalue) {
		delete[] data;
		bit_count = rvalue.bit_count;
		size_t bytes = byte_count();
		data = new unsigned char[bytes];
		memcpy(data, rvalue.data, bytes);
	}
	return *this;
}

// Внешние логические операторы (&, |, ^, <<, >>)
BoolVector operator&(const BoolVector& lvalue, const BoolVector& rvalue) {
	BoolVector result(lvalue);
	result &= rvalue;
	return result;
}

BoolVector operator|(const BoolVector& lvalue, const BoolVector& rvalue) {
	BoolVector result(lvalue);
	result |= rvalue;
	return result;
}

BoolVector operator^(const BoolVector& lvalue, const BoolVector& rvalue) {
	BoolVector result(lvalue);
	result ^= rvalue;
	return result;
}

BoolVector operator<<(const BoolVector& bv, size_t shift) {
	BoolVector result(bv);
	result <<= shift;
	return result;
}

BoolVector operator>>(const BoolVector& bv, size_t shift) {
	BoolVector result(bv);
	result >>= shift;
	return result;
}