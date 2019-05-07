#include <Python.h>
#include <iostream>
#include <sstream>
#include <string>

/*
 * Implements an example function.
 */
PyDoc_STRVAR(TestModule_example_doc, "example(obj, number)\
\
Example function");

PyObject* TestModule_example(PyObject* self, PyObject* args, PyObject* kwargs) {
	/* Shared references that do not need Py_DECREF before returning. */
	long divident = 0;
	long divisor = 0;

	/* Parse positional and keyword arguments */
	static char* keywords[] = { "divident", "divisor", nullptr };
	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii", keywords, &divident, &divisor)) {
		return nullptr;
	}

	/* Function implementation starts here */
	
	if (divisor == 0) {
		std::stringstream ss;
		ss << "Division by 0! " << divident << " / " << divisor;
		PyErr_SetString(PyExc_ValueError, ss.str().c_str());
		return nullptr;    /* return NULL indicates error */
	}

	return PyLong_FromLong(divident / divisor);
}

/*
 * List of functions to add to TestModule in exec_TestModule().
 */
static PyMethodDef TestModule_functions[] = {
	{ "division", (PyCFunction)TestModule_example, METH_VARARGS | METH_KEYWORDS, TestModule_example_doc },
	{ nullptr, nullptr, 0, nullptr } /* marks end of array */
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

	return 0; /* success */
}

/*
 * Documentation for TestModule.
 */
PyDoc_STRVAR(TestModule_doc, "The TestModule module");


static PyModuleDef_Slot TestModule_slots[] = {
	{ Py_mod_exec, exec_TestModule },
	{ 0, nullptr }
};

static PyModuleDef TestModule_def = {
	PyModuleDef_HEAD_INIT,
	"TestModule",
	TestModule_doc,
	0,              /* m_size */
	TestModule_functions, /* m_methods */
	TestModule_slots,
	nullptr,           /* m_traverse */
	nullptr,           /* m_clear */
	nullptr,           /* m_free */
};

PyMODINIT_FUNC PyInit_TestModule() {
	return PyModuleDef_Init(&TestModule_def);
}
