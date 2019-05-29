#pragma once

#include<vector>
#include "matrix.h"


class Calculator
{
private:
	template<class T>
	static bool isFormatValid(Matrix<T>);

	template<class T>
	static void incrementAllIterators(std::vector<typename std::vector<T>::iterator>& columnIterVectorB);

	template<class T>
	static int dotProduct(std::vector<T>& v1, std::vector<T>& v2);

public:
	static Matrix<long> matrixMultiplication(Matrix<long> matrixA, Matrix<long> matrixB);
};

