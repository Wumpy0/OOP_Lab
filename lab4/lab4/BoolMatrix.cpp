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

// Инверсия в i - ой компоненты j - ой строки
// Инверсия k компонент j - ой строки, начиная с i - ой компоненты
// Установка в 0 / 1 i - ой компоненты j - ой строки
// Установка в 0 / 1 k компонент j - ой строки, начиная с i - ой компоненты