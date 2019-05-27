#include "Calculator.h"
#include <stdexcept>
#include <vector>

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

Matrix<int> Calculator::matrixMultiplication(Matrix<int> matrixA, Matrix<int> matrixB) {
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



	std::vector<std::vector<int>::iterator> columnIterVectorB;

	for (auto columnIter = matrixB.begin(); columnIter != matrixB.end(); ++columnIter) {
		columnIterVectorB.push_back(columnIter->begin());
	}


	std::vector<std::vector<int>> matrixC;

	std::vector<int> tempRowC;


	for (auto iter = matrixB.begin()->begin(); iter != matrixB.begin()->end(); incrementAllIterators<int>(columnIterVectorB)) {
		std::vector<int> columnVectorB;
		for (auto columnVectorBIter = columnVectorB.begin(); columnVectorBIter != columnVectorB.end(); ++columnVectorBIter) {
			columnVectorB.push_back(*columnVectorBIter);
		}


		for (auto rowVectorA = matrixA.begin(); rowVectorA != matrixA.end(); ++rowVectorA) {

			int value = dotProduct<int>(columnVectorB, *rowVectorA);

			tempRowC.push_back(value);
		}
	}

	return matrixC;
}

template<class T>
void Calculator::incrementAllIterators(std::vector<std::vector<T>::iterator> & iteratorVector) {
	for (auto iteratorVectorIter = iteratorVector.begin(); iteratorVectorIter != iteratorVector.end(); ++iteratorVectorIter) {
		++* iteratorVectorIter;
	}
}