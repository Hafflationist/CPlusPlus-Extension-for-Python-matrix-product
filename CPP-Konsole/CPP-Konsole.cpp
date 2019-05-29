
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <stdexcept>

template<class T>
using Matrix = std::vector<std::vector<T>>;

template<class T>
bool isFormatValid(Matrix<T> matrix) {
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
int dotProduct(std::vector<T> & v1, std::vector<T> & v2) {
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

template<class T>
void incrementAllIterators(std::vector<typename std::vector<T>::iterator> & iteratorVector) {
	for (auto iteratorVectorIter = iteratorVector.begin(); iteratorVectorIter != iteratorVector.end(); ++iteratorVectorIter) {
		++* iteratorVectorIter;
	}
}

Matrix<long> matrixMultiplication(Matrix<long> matrixA, Matrix<long> matrixB) {
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



	std::vector<std::vector<long>::iterator> columnIterVectorB;

	for (auto columnIter = matrixB.begin(); columnIter != matrixB.end(); ++columnIter) {
		columnIterVectorB.push_back(columnIter->begin());
	}


	std::vector<std::vector<long>> matrixC;

	std::vector<long> tempRowC;
	std::cout << "Punkt 1" << std::endl;

	for (auto iter = matrixB.begin()->begin(); 
		iter != matrixB.begin()->end(); 
		incrementAllIterators<int>(columnIterVectorB), ++iter) {

		tempRowC.clear();
		std::vector<long> columnVectorB;

		for (auto columnVectorBIter = columnIterVectorB.begin(); 
			columnVectorBIter != columnIterVectorB.end(); 
			++columnVectorBIter) {

			columnVectorB.push_back(**columnVectorBIter);
		}

		std::cout << "Punkt 2 " << columnIterVectorB.size() << std::endl;

		std::cout << "Punkt 3 " << columnVectorB[0] << " | " << columnVectorB[1] << std::endl;

		for (auto rowVectorA = matrixA.begin(); rowVectorA != matrixA.end(); ++rowVectorA) {

			int value = dotProduct<int>(columnVectorB, *rowVectorA);

			tempRowC.push_back(value);
		}
		matrixC.push_back(tempRowC);
	}

	std::cout << "Punkt Return" << std::endl;
	return matrixC;
}



int main() {



	std::vector<std::vector<long>> matrixA = {
		{1,2},
		{2,3}
	};
	std::vector<std::vector<long>> matrixB = {
		{4,5},
		{5,6}
	};



	std::stringstream stringStream;
	auto m = matrixMultiplication(matrixA, matrixB);
	stringStream << "matrixC:\n" << m[0][0] << "\t" << m[1][0] << "\n"
		                         << m[0][1] << "\t" << m[1][1] << "\n";

	// 14 17
	// 23 28
	std::cout << stringStream.str().c_str() << std::endl;








	//int array[10];

	//int* begin = array;
	//int* end = &array[9];

	//for (int* iterator = begin; iterator <= end; iterator++) {
	//	*iterator = function();
	//}
	// ...
}

//int function() {
//
//	int stack = 0;
//
//	int* heap = new int();
//
//	delete heap;
//
//}



