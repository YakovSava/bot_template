# include <stdio.h>
# include <Python.h>
# include <iostream>
# include <string>
# include <fstream>
using namespace std;

string concatinate(string first, string second) { 
    string endline = "\n";
    return first + endline + second;
}

string Cread(const char* filename) {
    ifstream file(filename);
    string line, lines;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines = concatinate(lines, line);
        }
    } else {
        lines = "bad open";
    }
    file.close();
    return lines;
}

int Cwrite(const char* filename, const char* lines) {
    FILE* fm = fopen(filename, "wt");

    if (fm == NULL) {

        return 0;
    } else {

        fprintf(fm, "%s", lines);
        fclose(fm);

        return 1;
    }
}

static PyObject* write(PyObject *self, PyObject *args) {
    PyObject *filename_obj, *data_obj;

    if (!PyArg_ParseTuple(args, "UU", &filename_obj, &data_obj)) {
        return NULL;
    }

    const char *filename = PyUnicode_AsUTF8(filename_obj);
    const char *data = PyUnicode_AsUTF8(data_obj);

    Cwrite(filename, data);

    return Py_None;
}

static PyObject* read(PyObject *self, PyObject *args) {
    PyObject* filename_obj;

    if (!PyArg_ParseTuple(args, "U", &filename_obj)) {
        return NULL;
    }

    const char* filename = PyUnicode_AsUTF8(filename_obj);
    string read_result = Cread(filename);

    return PyUnicode_FromString(read_result.c_str());
}

static PyMethodDef methods[] = {
    {"read", read, METH_VARARGS, "C reading files"},
    {"write", write, METH_VARARGS, "C writing to file"},
    {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "binder",
    "Binder",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_binder(void) {
    return PyModule_Create(&module);
}