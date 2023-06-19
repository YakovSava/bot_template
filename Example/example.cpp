# include <Python.h>

static PyObject* test(PyObject* self, PyObject* args) {
    return Py_BuildValue("s", "Hello from C!")
}

static PyMethodDef methods[] = {
    {"test", test, METH_VARARGS, "Test"},
    {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "example",
    "Manipulation with files!",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_example(void) {
    return PyModule_Create(&module);
}