#include "BoolVector.h"

// ��������������� ������
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

// ������������:

// �� ���������
BoolVector::BoolVector() : data(nullptr), bit_count(0) {}
// � ����������� (������ � �������� - ���� � �� �� ��� ���� ��������)
BoolVector::BoolVector(size_t size, bool value) : bit_count(size) {
	size_t bytes = byte_count();
	data = new unsigned char[bytes];
	memset(data, value ? 0xFF : 0x00, bytes);
	clear_tail();
}
// ����������� �� ������� const char *
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
// ����������� �����������
BoolVector::BoolVector(const BoolVector& other) : bit_count(other.bit_count) {
	size_t bytes = byte_count();
	data = new unsigned char[bytes];
	memcpy(data, other.data, bytes);
}
// ����������
BoolVector::~BoolVector() {
	delete[] data;
}

// ��������� � 0 / 1 i - �� ����������
void BoolVector::set(size_t index) {
	check_index(index);
	data[index / 8] |= (1 << (index % 8));
}

void BoolVector::reset(size_t index) {
	check_index(index);
	data[index / 8] &= ~(1 << (index % 8));
}

// ����� (���������� ���) �������
size_t BoolVector::length() const {
	return bit_count;
}

// ����� ����������� � ������ �������� (swap)
void BoolVector::swap(BoolVector& other) {
	std::swap(data, other.data);
	std::swap(bit_count, other.bit_count);
}

// �������� ���� ��������� �������
void BoolVector::invert() {
	size_t bytes = byte_count();
	for (size_t i = 0; i < bytes; ++i)
		data[i] = ~data[i];
	clear_tail();
}

// �������� i-�� ����������
void BoolVector::invert(size_t index) {
	check_index(index);
	data[index / 8] ^= (1 << (index % 8));
}

// ��������� � 0/1 k ���������, ������� � i-��
void BoolVector::set_value(size_t index, bool value, size_t count) {
	check_index(index);
	assert(index + count <= bit_count);

	for (size_t i = index; i < index + count; ++i)
		value ? set(i) : reset(i);
}

// ��������� � 0/1 ���� ��������� �������
void BoolVector::set_all(bool value) {
	memset(data, value ? 0xFF : 0x00, byte_count());
	clear_tail();
}