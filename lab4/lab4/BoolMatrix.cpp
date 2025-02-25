#include "BoolMatrix.h"

// Вспомогательные методы
void BoolMatrix::checkRow(size_t index) const {
	assert(index < rows_);
}
void BoolMatrix::checkCol(size_t index) const {
	assert(index < cols_);
}

// Конструкторы 
// По умолчанию 
BoolMatrix::BoolMatrix() :
	rows_(0),
	cols_(0) {}

// С параметрами (количество строк/столбцов и значения разрядов)
BoolMatrix::BoolMatrix(size_t rows, size_t cols, bool value) :
	rows_(rows),
	cols_(cols) 
{
	for (size_t i = 0; i < rows_; ++i) {
		matrix_.emplace_back(cols_, value);
	}
}

// Конструктор из матрицы char
BoolMatrix::BoolMatrix(const std::vector<const char*>& charMatrix) {
	if (charMatrix.empty()) {
		rows_ = 0;
		cols_ = 0;
		return;
	}

	rows_ = charMatrix.size();
	cols_ = strlen(charMatrix[0]);

	for (const char* row : charMatrix) {
		assert(strlen(row) == cols_);
		matrix_.emplace_back(row);
	}
}

// Конструктор копирования
BoolMatrix::BoolMatrix(const BoolMatrix& other) :
	rows_(other.rows_),
	cols_(other.cols_),
	matrix_(other.matrix_) {}

// Деструктор

// Получение числа строк и столбцов матрицы
size_t BoolMatrix::getRows() const {
	return rows_;
}

size_t BoolMatrix::getCols() const {
	return cols_;
}

// Обмен содержимого с другой матрицей (swap)
void BoolMatrix::swap(BoolMatrix& other) {
	matrix_.swap(other.matrix_);
	std::swap(rows_, other.rows_);
	std::swap(cols_, other.cols_);
}

// Ввод / вывод в консоль(потоковый)
std::ostream& operator<<(std::ostream& os, const BoolMatrix& bm) {
	for (const BoolVector& row : bm.matrix_) {
		os << row << '\n';
	}
	return os;
}

// Вес матрицы(количество единичных компонент)
size_t BoolMatrix::weight() const {
	size_t count = 0;
	for (const BoolVector& raw : matrix_) {
		count += raw.weight();
	}
	return count;
}

// Конъюнкция всех строк(возвращает булев вектор)
BoolVector BoolMatrix::conjunction() {
	BoolVector result = matrix_[0];
	for (size_t i = 1; i < rows_; ++i) {
		result &= matrix_[i];
	}
	return result;
}

// Дизъюнкция всех строк(возвращает булев вектор)
BoolVector BoolMatrix::disjunction() {
	BoolVector result = matrix_[0];
	for (size_t i = 1; i < rows_; ++i) {
		result |= matrix_[i];
	}
	return result;
}

// Вес j - ой строки
size_t BoolMatrix::rowWeight(size_t j) const {
	checkRow(j);
	return matrix_[j].weight();
}

// Инверсия i - ой компоненты j - ой строки + 
// инверсия k компонент j - ой строки, начиная с i - ой компоненты
void BoolMatrix::invert(size_t j, size_t i, size_t count) {
	checkRow(j);
	checkCol(i);
	if (count > 1) {
		assert(i + count <= cols_);
	}
	for (size_t pos = i; pos < i + count; ++pos) {
		matrix_[j].invert(pos);
	}
}

// Установка в 0 / 1 i - ой компоненты j - ой строки + 
// установка в 0 / 1 k компонент j - ой строки, начиная с i - ой компоненты
void BoolMatrix::setValue(size_t j, size_t i, bool value, size_t count) {
	checkRow(j);
	checkCol(i);
	if (count > 1) {
		assert(i + count <= cols_);
	}
	for (size_t pos = i; pos < i + count; ++pos) {
		value ? matrix_[j].set(pos) : matrix_[j].reset(pos);
	}
}

// Присваивание(=)
BoolMatrix& BoolMatrix::operator=(const BoolMatrix& rhs) {
	if (this != &rhs) {
		matrix_ = rhs.matrix_;
		rows_ = rhs.rows_;
		cols_ = rhs.cols_;
	}
	return *this;
}
// Получение строки([])

// Построчное побитовое умножение(&=)

// Построчное побитовое сложение(|=)

// Построчное побитовое исключающее ИЛИ(^=)

// Построчная побитовая инверсия(~)
BoolMatrix BoolMatrix::operator~() const {
	BoolMatrix result(*this);
	for (BoolVector& row : result.matrix_) {
		row = ~row;
	}
	return result;
}