#include "BoolMatrix.h"

// Вспомогательные методы
void BoolMatrix::checkRow(size_t index) const {
	assert(index < rows);
}
void BoolMatrix::checkCol(size_t index) const {
	assert(index < cols);
}

// Конструкторы 
// По умолчанию 
BoolMatrix::BoolMatrix() :
	rows(0),
	cols(0) {}

// С параметрами (количество строк/столбцов и значения разрядов)
BoolMatrix::BoolMatrix(size_t rows, size_t cols, bool value) :
	rows(rows),
	cols(cols) 
{
	for (size_t i = 0; i < rows; ++i) {
		matrix.emplace_back(cols, value);
	}
}

// Конструктор из матрицы char
BoolMatrix::BoolMatrix(const std::vector<const char*>& charMatrix) {
	if (charMatrix.empty()) {
		rows = 0;
		cols = 0;
		return;
	}

	rows = charMatrix.size();
	cols = strlen(charMatrix[0]);

	for (const char* row : charMatrix) {
		assert(strlen(row) == cols);
		matrix.emplace_back(row);
	}
}

// Конструктор копирования
BoolMatrix::BoolMatrix(const BoolMatrix& other) :
	rows(other.rows),
	cols(other.cols),
	matrix(other.matrix) {}

// Деструктор

// Получение числа строк и столбцов матрицы
size_t BoolMatrix::getRows() const {
	return rows;
}

size_t BoolMatrix::getCols() const {
	return cols;
}

// Обмен содержимого с другой матрицей (swap)
void BoolMatrix::swap(BoolMatrix& other) {
	matrix.swap(other.matrix);
	std::swap(rows, other.rows);
	std::swap(cols, other.cols);
}

// Ввод / вывод в консоль(потоковый)
std::ostream& operator<<(std::ostream& os, const BoolMatrix& bm) {
	for (const BoolVector& row : bm.matrix) {
		os << row << '\n';
	}
	return os;
}

// Вес матрицы(количество единичных компонент)
size_t BoolMatrix::weight() const {
	size_t count = 0;
	for (const BoolVector& raw : matrix) {
		count += raw.weight();
	}
	return count;
}

// Конъюнкция всех строк(возвращает булев вектор)
BoolVector BoolMatrix::conjunction() {
	BoolVector result = matrix[0];
	for (size_t i = 1; i < rows; ++i) {
		result &= matrix[i];
	}
	return result;
}

// Дизъюнкция всех строк(возвращает булев вектор)
BoolVector BoolMatrix::disjunction() {
	BoolVector result = matrix[0];
	for (size_t i = 1; i < rows; ++i) {
		result |= matrix[i];
	}
	return result;
}

// Вес j - ой строки
size_t BoolMatrix::rowWeight(size_t j) const {
	checkRow(j);
	return matrix[j].weight();
}

// Инверсия i - ой компоненты j - ой строки + инверсия k компонент j - ой строки, начиная с i - ой компоненты
void BoolMatrix::invert(size_t j, size_t i, size_t count) {
	count -= 1;
	checkRow(j);
	checkCol(i);
	if (count) {
		checkCol(i + count);
	}
	for (size_t pos = i; pos <= i + count; ++pos) {
		matrix[j].invert(pos);
	}
}
// Установка в 0 / 1 i - ой компоненты j - ой строки + установка в 0 / 1 k компонент j - ой строки, начиная с i - ой компоненты
void BoolMatrix::setValue(size_t j, size_t i, bool value, size_t count) {
	count -= 1;
	checkRow(j);
	checkCol(i);
	if (count) {
		checkCol(i + count);
	}
	for (size_t pos = i; pos <= i + count; ++pos) {
		value ? matrix[j].set(pos) : matrix[j].reset(pos);
	}
}