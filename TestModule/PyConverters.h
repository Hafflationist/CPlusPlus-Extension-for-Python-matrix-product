#pragma once
#include <Python.h>
#include "matrix.h"

extern Matrix<long> PyList_ToMatrix(PyObject* object);
extern PyObject* PyList_FromMatrix(Matrix<long> matrix);