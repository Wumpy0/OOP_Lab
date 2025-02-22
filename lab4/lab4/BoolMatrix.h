#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include "../../lab3/lab3/BoolVector.h"

class BoolMatrix
{
public:
	// Конструкторы 
	// По умолчанию 
	BoolMatrix();
	// С параметрами (количество строк/столбцов и значения разрядов)
	BoolMatrix(size_t rows, size_t cols, bool value = false);
	// Конструктор из матрицы char
	
	// Конструктор копирования
	BoolMatrix(const BoolMatrix& other);
	// Деструктор

	// Получение числа строк и столбцов матрицы
	size_t getRows() const;
	size_t getCols() const;
	// Обмен содержимого с другой матрицей (swap)
	void swap(BoolMatrix& other);
	// Ввод / вывод в консоль(потоковый)
	friend std::ostream& operator<<(std::ostream& os, const BoolMatrix& bm);

	// Вес матрицы(количество единичных компонент)
	size_t weight() const;
	// Конъюнкция всех строк(возвращает булев вектор)
	BoolVector conjunction();
	// Дизъюнкция всех строк(возвращает булев вектор)
	BoolVector disjunction();
	// Вес j - ой строки
	size_t rowWeight(size_t j) const;
	// Инверсия в i - ой компоненты j - ой строки
	
	// Инверсия k компонент j - ой строки, начиная с i - ой компоненты
	
	// Установка в 0 / 1 i - ой компоненты j - ой строки
	
	// Установка в 0 / 1 k компонент j - ой строки, начиная с i - ой компоненты

private:
	std::vector<BoolVector> matrix;
	size_t rows;
	size_t cols;
private:
	// Вспомогательные методы
	void checkRow(size_t index) const;
	void checkCol(size_t index) const;
};

