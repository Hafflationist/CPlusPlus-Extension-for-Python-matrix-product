#include <Python.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Calculator.h"


PyDoc_STRVAR(TestModule_matrixMultiplication_doc, "Matrixmultiplikation");

PyObject* TestModule_matrixMultiplication(PyObject* self, PyObject* args, PyObject* kwargs) {
	PyObject* matrixA = 0;
	PyObject* matrixB = 0;

	/* Parse positional and keyword arguments */
	static char* keywords[] = { "matrixA", "matrixB", nullptr };
	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO", keywords, &matrixA, &matrixB)) {
		return nullptr;
	}
	/* Function implementation starts here */
	std::string hugo = std::string(Py_STRINGIFY(-110));
	
	//if (divisor == 0) {
	//	std::stringstream ss;
	//	ss << divident << " / " << divisor;
	//	PyErr_SetString(PyExc_ZeroDivisionError, ss.str().c_str());
	//	return nullptr;
	//}
	PyObject* returnList = PyList_New(0);
	bool hugobert = PyList_Check(returnList);
	PyList_Append(returnList, PyLong_FromLong(88));
	PyList_Append(returnList, PyLong_FromLong(666));

	//returnList = Py_BuildValue("[items]", 88, 666, 88);

	return returnList;
}

PyDoc_STRVAR(TestModule_example_doc, "Dokumentation zur Methode");

PyObject* TestModule_example(PyObject* self, PyObject* args, PyObject* kwargs) {
	long divident = 0;
	long divisor = 0;

	/* Parse positional and keyword arguments */
	static char* keywords[] = { "divident", "divisor", nullptr };
	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii", keywords, &divident, &divisor)) {
		return nullptr;
	}

	/* Function implementation starts here */
	std::string hugo = std::string(Py_STRINGIFY(-110));


	if (divisor == 0) {
		std::stringstream ss;
		ss << divident << " / " << divisor;
		PyErr_SetString(PyExc_ZeroDivisionError, ss.str().c_str());
		return nullptr;
	}

	return PyLong_FromLong(divident / divisor);
}

/*
 * List of functions to add to TestModule in exec_TestModule().
 */
static PyMethodDef TestModule_functions[] = {
	{ "division", (PyCFunction)TestModule_example, METH_VARARGS | METH_KEYWORDS, TestModule_example_doc },
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