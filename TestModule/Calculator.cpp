#include "Calculator.h"
#include <stdexcept>
#include <vector>

#include <iostream>

template<class T>
using Matrix = std::vector<std::vector<T>>;

template<class T>
bool Calculator::isFormatValid(Matrix<T> matrix) {
	if (matrix.size() <= 0)
		return false;

	int firstSize = matrix[0].size();
	if (firstSize <= 0)
		return false;

	for (auto row_ptr = matrix.begin(); row_ptr != matrix.end(); ++row_ptr) {
		if (row_ptr->size() != firstSize)
			return false;
	}

	return true;
}


template<class T>
int Calculator::dotProduct(std::vector<T> & v1, std::vector<T> & v2) {
	if (v1.size() != v2.size())
		throw std::invalid_argument("Inavlid format!");
	auto v1Iter = v1.begin();
	auto v2Iter = v2.begin();
	std::vector<T> temp;
	for (; v1Iter != v1.end(); ++v1Iter, ++v2Iter) {
		T value = *v1Iter * *v2Iter;
		temp.push_back(value);
	}

	int acc = 0;

	for (auto tempIter = temp.begin(); tempIter != temp.end(); ++tempIter) {
		acc += *tempIter;
	}

	return acc;
}

Matrix<long> Calculator::matrixMultiplication(Matrix<long> matrixA, Matrix<long> matrixB) {
	// Validate format:
	bool isValidA = isFormatValid(matrixA);
	bool isValidB = isFormatValid(matrixB);

	if (!isValidA || !isValidB) {
		throw std::invalid_argument("Inavlid format!");
	}

	int k = matrixA.size();
	int l_A = matrixA[0].size();
	int l_B = matrixB.size();
	int m = matrixB[0].size();

	if (l_A != l_B)
		throw std::invalid_argument("Inavlid format!");

	std::vector<std::vector<long>> matrixC;
	std::vector<long> tempRowC;

	for (auto rowVectorA = matrixA.begin(); rowVectorA != matrixA.end(); ++rowVectorA) {

		std::vector<std::vector<long>::iterator> columnIterVectorB;

		for (auto columnIter = matrixB.begin(); columnIter != matrixB.end(); ++columnIter) {
			columnIterVectorB.push_back(columnIter->begin());
		}

		tempRowC.clear();

		for (auto iter = matrixB.begin()->begin();
			iter != matrixB.begin()->end();
			incrementAllIterators<long>(columnIterVectorB), ++iter) {

			std::vector<long> columnVectorB;
			for (auto columnVectorBIter = columnIterVectorB.begin();
				columnVectorBIter != columnIterVectorB.end();
				++columnVectorBIter) {
				columnVectorB.push_back(**columnVectorBIter);
			}

			int value = dotProduct<long>(columnVectorB, *rowVectorA);
			tempRowC.push_back(value);
		}
		matrixC.push_back(tempRowC);
	}
	return matrixC;
}

template<class T>
void Calculator::incrementAllIterators(std::vector<typename std::vector<T>::iterator> & iteratorVector) {
	for (auto iteratorVectorIter = iteratorVector.begin(); iteratorVectorIter != iteratorVector.end(); ++iteratorVectorIter) {
		++* iteratorVectorIter;
	}
}