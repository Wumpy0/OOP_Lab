#include "BoolVector.h"

// Rank
BoolVector::Rank::Rank(unsigned char* byte_ptr, size_t bit) :
	byte_(byte_ptr), 
	bit_(bit) {};

BoolVector::Rank::operator bool() const {
	return (*byte_ >> bit_) & 1;
}

BoolVector::Rank& BoolVector::Rank::operator=(bool value) {
	if (value) { 
		*byte_ |= (1 << bit_);
	}
	else { 
		*byte_ &= ~(1 << bit_);
	};
	return *this;
}

// Вспомогательные методы
size_t BoolVector::byteCount() const {
	return (bitCount_ + 7) / 8;
}

void BoolVector::clearTail() {
	size_t extra_bits = bitCount_ % 8;
	if (extra_bits != 0) {
		data_[byteCount() - 1] &= (0xFF >> (8 - extra_bits));
	}
}

void BoolVector::checkIndex(size_t index) const {
	assert(index < bitCount_);
}

void BoolVector::checkSize(const BoolVector& other) const {
	assert(bitCount_ == other.bitCount_);
}

// Конструкторы:

// По умолчанию
BoolVector::BoolVector() : 
	data_(nullptr), 
	bitCount_(0) {}
// С параметрами (размер и значение - одно и то же для всех разрядов)
BoolVector::BoolVector(size_t size, bool value) : bitCount_(size) {
	size_t bytes = byteCount();
	data_ = new unsigned char[bytes];
	memset(data_, value ? 0xFF : 0x00, bytes);
	clearTail();
}
// Конструктор из массива const char *
BoolVector::BoolVector(const char* str) {
	bitCount_ = strlen(str);
	size_t bytes = byteCount();
	data_ = new unsigned char[bytes] {};

	for (size_t i = 0; i < bitCount_; ++i) {
		if (str[i] == '1') {
			set(i);
		}
		else {
			assert(str[i] == '0');
		}
	}
}
// Конструктор копирования
BoolVector::BoolVector(const BoolVector& other) : bitCount_(other.bitCount_) {
	size_t bytes = byteCount();
	data_ = new unsigned char[bytes];
	memcpy(data_, other.data_, bytes);
}
// Деструктор
BoolVector::~BoolVector() {
	delete[] data_;
}

// Установка в 0 / 1 i - ой компоненты
void BoolVector::set(size_t index) {
	checkIndex(index);
	data_[index / 8] |= (1 << (index % 8));
}

void BoolVector::reset(size_t index) {
	checkIndex(index);
	data_[index / 8] &= ~(1 << (index % 8));
}

// Длина (количество бит) вектора
size_t BoolVector::length() const {
	return bitCount_;
}

// Вес вектора (количество единичных компонент)
size_t BoolVector::weight() const {
	size_t count = 0;
	for (size_t i = 0; i < bitCount_; ++i) {
		if ((*this)[i]) {
			++count;
		}
	}
	return count;
}

// Получение компоненты([])
BoolVector::Rank BoolVector::operator[](size_t index) {
	checkIndex(index);
	return Rank(&data_[index / 8], index % 8);
}

bool BoolVector::operator[](size_t index) const {
	checkIndex(index);
	return (data_[index / 8] >> (index % 8)) & 1;
}

// Ввод/вывод
std::ostream& operator<<(std::ostream& os, const BoolVector& bv) {
	for (size_t i = 0; i < bv.bitCount_; ++i)
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
	std::swap(data_, other.data_);
	std::swap(bitCount_, other.bitCount_);
}

// Инверсия всех компонент вектора
void BoolVector::invert() {
	size_t bytes = byteCount();
	for (size_t i = 0; i < bytes; ++i)
		data_[i] = ~data_[i];
	clearTail();
}

// Инверсия i-ой компоненты
void BoolVector::invert(size_t index) {
	checkIndex(index);
	data_[index / 8] ^= (1 << (index % 8));
}

// Установка в 0/1 k компонент, начиная с i-ой
void BoolVector::setValue(size_t index, bool value, size_t count) {
	checkIndex(index);
	assert(index + count <= bitCount_);

	for (size_t i = index; i < index + count; ++i)
		value ? set(i) : reset(i);
}

// Установка в 0/1 всех компонент вектора
void BoolVector::setAll(bool value) {
	memset(data_, value ? 0xFF : 0x00, byteCount());
	clearTail();
}

// Побитовое умножение(&=)
BoolVector& BoolVector::operator&=(const BoolVector& rhs) {
	checkSize(rhs);
	for (size_t i = 0; i < byteCount(); ++i)
		data_[i] &= rhs.data_[i];
	return *this;
}

// Побитовое сложение(|=)
BoolVector& BoolVector::operator|=(const BoolVector& rhs) {
	checkSize(rhs);
	for (size_t i = 0; i < byteCount(); ++i)
		data_[i] |= rhs.data_[i];
	return *this;
}

// Побитовое исключающее ИЛИ(^=)
BoolVector& BoolVector::operator^=(const BoolVector& rhs) {
	checkSize(rhs);
	for (size_t i = 0; i < byteCount(); ++i)
		data_[i] ^= rhs.data_[i];
	return *this;
}

// Побитовые сдвиги(<<=, >>=)
BoolVector& BoolVector::operator<<=(size_t shift) {
	if (shift >= bitCount_) {
		setAll(false);
		return *this;
	}

	size_t byte_shift = shift / 8;
	size_t bit_shift = shift % 8;
	size_t bytes = byteCount();
	if (byte_shift > 0) {
		for (size_t i = 0; i < bytes - byte_shift; ++i) {
			data_[i] = data_[i + byte_shift];
		}
		memset(data_ + bytes - byte_shift, 0, byte_shift);
	}
	
	if (bit_shift > 0) {
		for (size_t i = 0; i < bytes - 1; ++i) {
			data_[i] = (data_[i] >> bit_shift) | (data_[i + 1] << (8 - bit_shift));
		}
		data_[bytes - 1] <<= bit_shift;
	}

	clearTail();
	return *this;
}

BoolVector& BoolVector::operator>>=(size_t shift) {
	if (shift >= bitCount_) {
		setAll(false);
		return *this;
	}

	size_t byte_shift = shift / 8;
	size_t bit_shift = shift % 8;
	size_t bytes = byteCount();
	if (byte_shift > 0) {
		for (size_t i = bytes - 1; i >= byte_shift; --i) {
			data_[i] = data_[i - byte_shift];
		}
		memset(data_, 0, byte_shift);
	}
	
	if (bit_shift > 0) {
		for (size_t i = bytes - 1; i > 0; --i) {
			data_[i] = (data_[i] << bit_shift) | (data_[i - 1] >> (8 - bit_shift));
		}
		data_[0] <<= bit_shift;
	}

	clearTail();
	return *this;
}

// Побитовая инверсия(~)
BoolVector BoolVector::operator~() const {
	BoolVector result(*this);
	result.invert();
	return result;
}

// Присваивание(=)
BoolVector& BoolVector::operator=(const BoolVector& rhs) {
	if (this != &rhs) {
		delete[] data_;
		bitCount_ = rhs.bitCount_;
		size_t bytes = byteCount();
		data_ = new unsigned char[bytes];
		memcpy(data_, rhs.data_, bytes);
	}
	return *this;
}

// Внешние логические операторы (&, |, ^, <<, >>)
BoolVector operator&(const BoolVector& lhs, const BoolVector& rhs) {
	BoolVector result(lhs);
	result &= rhs;
	return result;
}

BoolVector operator|(const BoolVector& lhs, const BoolVector& rhs) {
	BoolVector result(lhs);
	result |= rhs;
	return result;
}

BoolVector operator^(const BoolVector& lhs, const BoolVector& rhs) {
	BoolVector result(lhs);
	result ^= rhs;
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