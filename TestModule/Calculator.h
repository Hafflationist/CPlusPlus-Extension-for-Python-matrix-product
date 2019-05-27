#pragma once

#include<vector>

template<class T>
using Matrix = std::vector<std::vector<T>>;

static class Calculator
{
private:
	template<class T>
	static bool isFormatValid(Matrix<T>);

	template<class T>
	static void incrementAllIterators(std::vector<std::vector<T>::iterator>& columnIterVectorB);

	template<class T>
	static int dotProduct(std::vector<T>& v1, std::vector<T>& v2);

public:
	static Matrix<int> matrixMultiplication(Matrix<int> matrixA, Matrix<int> matrixB);
};

