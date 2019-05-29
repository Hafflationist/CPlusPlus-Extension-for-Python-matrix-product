#include "PyConverters.h"
#include <exception>

Matrix<long> PyList_ToMatrix(PyObject* object) {

	if (!PyList_Check(object))
		throw std::exception("Hugobert");
	auto rows = PyList_Size(object);

	if (rows == 0) {
		return Matrix<long>();
	}

	auto firstRow = PyList_GetItem(object, 0);
	auto columns = PyList_Size(firstRow);
	if (columns == 0) {
		return Matrix<long>();
	}

	// Checking for shape:
	for (size_t i = 0; i < rows; i++) {

		auto row = PyList_GetItem(object, i);
		if (!PyList_Check(row)) {
			throw std::exception("No nested list!");
		}
		auto rowLength = PyList_Size(row);
		//PyLong_AsLong(row)
		if (rowLength != (int)columns) {
			throw std::exception("No valid shape!");
		}
	}

	Matrix<long> newMatrix;
	for (size_t i = 0; i < rows; i++) {
		std::vector<long> newRow;
		auto row = PyList_GetItem(object, i);
		auto rowLength = PyList_Size(row);

		for (size_t j = 0; j < rowLength; j++) {
			auto element = PyList_GetItem(row, j);
			auto value = PyLong_AsLong(element);
			newRow.push_back(value);
		}
		newMatrix.push_back(newRow);
	}

	return newMatrix;
}



PyObject* PyList_FromMatrix(Matrix<long> matrix) {
	PyObject* object = PyList_New(matrix.size());

	for (size_t i = 0; i < matrix.size(); i++) {
		PyObject* nestedObject = PyList_New(matrix[i].size());
		for (size_t j = 0; j < matrix[i].size(); j++) {
			PyObject* value = PyLong_FromLong(matrix[i][j]);
			PyList_SetItem(nestedObject, j, value);
		}
		PyList_SetItem(object, i, nestedObject);
	}

	return object;
}
