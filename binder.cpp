# include <iostream>
# include <fstream>
# include <string>
# include <Python.h>
using namespace std;

string concatinate(const string& first, const string& second) { 
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
    ofstream file(filename);
    if (file.is_open()) {
        file << lines << endl;
        file.close();
        return 1;
    } else {
        file.close();
        return 0;
    }
}

static PyObject* write(PyObject* self, PyObject* args) {
    PyObject *filename_obj, *data_obj;

    if (!PyArg_ParseTuple(args, "UU", &filename_obj, &data_obj)) {
        return NULL;
    }

    const char *filename = PyUnicode_AsUTF8(filename_obj);
    const char *data = PyUnicode_AsUTF8(data_obj);

    int result = Cwrite(filename, data);

    delete filename, data;

    Py_DECREF(filename_obj);
    Py_DECREF(data_obj);

    Py_RETURN_NONE;
}

static PyObject* read(PyObject* self, PyObject* args) {
    PyObject* filename_obj;

    if (!PyArg_ParseTuple(args, "U", &filename_obj)) {
        return NULL;
    }

    const char* filename = PyUnicode_AsUTF8(filename_obj);
    string read_result = Cread(filename);

    delete filename;

    Py_DECREF(filename_obj);

    return PyUnicode_FromString(read_result.c_str());
}

static PyMethodDef methods[] = {
    {"read", read, METH_VARARGS, "Read file (C++)"},
    // {"write", write, METH_VARARGS, "Write to file (C++)"},
    {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "binder",
    "Manipulation with files!",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_binder(void) {
    return PyModule_Create(&module);
}