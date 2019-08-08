#include <Python.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Calculator.h"
#include "PyConverters.h"
#include "matrix.h"


PyDoc_STRVAR(TestModule_matrixMultiplication_doc, "Matrixmultiplikation");

PyObject* TestModule_matrixMultiplication(PyObject* self, PyObject* args, PyObject* kwargs) {
	PyObject* matrixA_obj = nullptr;
	PyObject* matrixB_obj = nullptr;

	static char* keywords[] = { "matrixA", "matrixB", nullptr };
	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO", keywords, &matrixA_obj, &matrixB_obj)) {
		PyErr_SetString(PyExc_TypeError, "Wrong type of parameters!");
		return nullptr;
	}

	Matrix<long> matrixA;
	Matrix<long> matrixB;

	try {
		matrixA = PyList_ToMatrix(matrixA_obj);
		matrixB = PyList_ToMatrix(matrixB_obj);
	}
	catch (const std::exception& exception) {
		PyErr_SetString(PyExc_TypeError, exception.what());
		return nullptr;
	}

	Matrix<long> resultMatrix = Calculator::matrixMultiplication(matrixA, matrixB);

	return PyList_FromMatrix(resultMatrix);
}

/*
 * List of functions to add to TestModule in exec_TestModule().
 */
static PyMethodDef TestModule_functions[] = {
	{ "matrixMultiplication", (PyCFunction)TestModule_matrixMultiplication, METH_VARARGS | METH_KEYWORDS, TestModule_matrixMultiplication_doc },
	{ nullptr, nullptr, 0, nullptr } // marks end of array
};

/*
 * Initialize TestModule. May be called multiple times, so avoid
 * using static state.
 */
int exec_TestModule(PyObject* module) {
	PyModule_AddFunctions(module, TestModule_functions);

	PyModule_AddStringConstant(module, "__author__", "Marcel Robohm");
	PyModule_AddStringConstant(module, "__version__", "1.0.0");
	PyModule_AddIntConstant(module, "year", 2019);

	return 0;
}


PyDoc_STRVAR(TestModule_doc, "Dokumentation des Moduls");


static PyModuleDef_Slot TestModule_slots[] = {
	{ Py_mod_exec, exec_TestModule },
	{ 0, nullptr }
};

static PyModuleDef TestModule_def = {
	PyModuleDef_HEAD_INIT,
	"TestModule",
	TestModule_doc,
	0,						// Größe des benötigten Modulspeichers
	TestModule_functions,	// Methodenliste
	TestModule_slots,
	nullptr,				// Funktionen bei GC-Traversal
	nullptr,				// Destruktor mit Löschen
	nullptr,				// Moduldestruktor
};

PyMODINIT_FUNC PyInit_TestModule() {
	return PyModuleDef_Init(&TestModule_def);
}