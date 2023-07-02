# include <Python.h>
# include <iostream>
# include <string>
# include <fstream>
# include <stdio.h>
# include <stdint.h>
using namespace std;


class Binder {
public:
    Binder() {};

    string read(const char* filename) {
        ifstream file(filename);
        string line, lines;

        if (file.is_open()) {
            while (getline(file, line)) {
                lines = this->concatinate(lines, line);
            }
        } else {
            lines = "bad open";
        }
        file.close();
        return lines;
    }

    int write(const char* filename, const char* lines) {
        FILE fm = fopen(filename, 'w');
        if (fm == NULL) {
            return 0;
        } else {
            fprintf(аь, "%ld", (intptr_t)lines);
            fclose(fm);
            return 1;
        }
    }
private:
    string concatinate(string first, string second) { 
        string endline = "\n";
        return first + endline + second;
    }
};

typedef struct {
    PyObject_HEAD
    Binder *obj;
} py_Binder;

static PyObject *py_Binder_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    py_Binder *self;
    self = (py_Binder *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->obj = NULL;
    }
    return (PyObject *) self;
}

// Метод для инициализации объекта
static int py_Binder_init(py_Binder *self, PyObject *args, PyObject *kwds) {
    self->obj = new Binder();
    return 0;
}

// Метод для освобождения ресурсов
static void py_Binder_dealloc(py_Binder *self) {
    delete self->obj;
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *py_Binder_write(py_Binder *self, PyObject *args) {
    PyObject *filename_obj, *data_obj;

    if (!PyArg_ParseTuple(args, "UU", &filename_obj, &data_obj)) {
        return NULL;
    }

    const char *filename = PyUnicode_AsUTF8(filename_obj);
    const char *data = PyUnicode_AsUTF8(data_obj);

    self->obj->write(filename, data);

    Py_DECREF(filename_obj);
    Py_DECREF(data_obj);

    return Py_None;
}

static PyObject* py_Binder_read(py_Binder *self, PyObject *args) {
    PyObject* filename_obj;

    if (!PyArg_ParseTuple(args, "U", &filename_obj)) {
        return NULL;
    }

    const char* filename = PyUnicode_AsUTF8(filename_obj);
    string read_result = self->obj->read(filename);

    delete filename;

    Py_DECREF(filename_obj);

    return PyUnicode_FromString(read_result.c_str());
}

// Методы класса
static PyMethodDef py_Binder_methods[] = {
    {"write", (PyCFunction) py_Binder_write, METH_NOARGS, "Binder write to file method"},
    {"read", (PyCFunction) py_Binder_write, METH_NOARGS, "Binder read file method"},
    {NULL} /* Sentinel */
};

// Тип объекта
static PyTypeObject py_BinderType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "binder.Binder", /* tp_name */
    sizeof(py_Binder), /* tp_basicsize */
    0, /* tp_itemsize */
    (destructor) py_Binder_dealloc, /* tp_dealloc */
    0, /* tp_print */
    0, /* tp_getattr */
    0, /* tp_setattr */
    0, /* tp_reserved */
    0, /* tp_repr */
    0, /* tp_as_number */
    0, /* tp_as_sequence */
    0, /* tp_as_mapping */
    0, /* tp_hash  */
    0, /* tp_call */
    0, /* tp_str */
    0, /* tp_getattro */
    0, /* tp_setattro */
    0, /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "Binder objects", /* tp_doc */
    0, /* tp_traverse */
    0, /* tp_clear */
    0, /* tp_richcompare */
    0, /* tp_weaklistoffset */
    0, /* tp_iter */
    0, /* tp_iternext */
    py_Binder_methods, /* tp_methods */
    0, /* tp_members */
    0, /* tp_getset */
    0, /* tp_base */
    0, /* tp_dict */
    0, /* tp_descr_get */
    0, /* tp_descr_set */
    0, /* tp_dictoffset */
    (initproc) py_Binder_init, /* tp_init */
    0, /* tp_alloc */
    py_Binder_new, /* tp_new */
};

// Модуль Python
static PyModuleDef moduleName_module = {
    PyModuleDef_HEAD_INIT,
    "binder", /* name of module */
    "Write and read files with C++ functions", /* module documentation */
    -1,
};

// Инициализация модуля
PyMODINIT_FUNC PyInit_binder(void) {
    PyObject *m;

    // Зарегистрируем тип класса
    if (PyType_Ready(&py_BinderType) < 0)
        return NULL;

    // Создаем модуль
    m = PyModule_Create(&moduleName_module);
    if (m == NULL)
        return NULL;

    // Добавляем тип класса в модуль
    Py_INCREF(&py_BinderType);
    PyModule_AddObject(m, "Binder", (PyObject *) &py_BinderType);

    return m;
}