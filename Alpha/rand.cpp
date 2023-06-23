# include <Python.h>
# include <cstdlib>
# include <ctime>
# include <string>
using namespace std;

class Random {
public:
  Random(int seed) {
    if (seed == 0) {
      srand(time(NULL));
    } else {
      srand(seed);
    }
  };

  int randint(int range_min, int range_max) {
    return ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
  }
};

typedef struct {
    PyObject_HEAD
    Random *obj;
} py_Random;

static const char* keywords[] = { "seed", nullptr };

static PyObject *py_Random_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    py_Random *self;
    self = (py_Random *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->obj = NULL;
    }
    return (PyObject *) self;
}

static int py_Random_init(py_Random *self, PyObject *args, PyObject *kwargs) {
    const char* seed_str;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s", (char**)keywords, &seed_str)) {
        return -1;
    }

    int seed = stoi(seed_str);

    self->obj = new Random(seed);

    return 0;
}

// Метод для освобождения ресурсов
static void py_Random_dealloc(py_Random *self) {
    delete self->obj;
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *py_Random_randint(py_Random *self, PyObject *args) {
    int range_min, range_max;

    if (!PyArg_ParseTuple(args, "ii", &range_min, &range_max)) {
        return NULL;
    }

    int result = self->obj->randint(range_min, range_max);

    return Py_BuildValue("i", result);
}

static PyObject *py_Random_choice(py_Random *self, PyObject *args) {
    PyObject* lst;

    if (!PyArg_ParseTuple(args, "O", &lst)) {
        return NULL;
    }

    if (!PyList_Check(lst)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }

    int size = PyList_Size(lst);
    int index = self->obj->randint(0, size);

    PyObject* item = PyList_GetItem(lst, index);

    Py_INCREF(item);

    return item;
}

// static PyObject *py_Random_shuffle(py_Random *self, PyObject *args) {
//     PyObject* lst;
//     PyObject* final_list = Py_BuildValue('[]', {});

//     if (!PyArg_ParseTuple(args, "O", &lst)) {
//         return NULL;
//     }

//     if (!PyList_Check(lst)) {
//         PyErr_SetString(PyExc_TypeError, "Expected a list object.");
//         return NULL;
//     }

//     int size = PyList_Size(lst);
//     for (int i = 0; i < size; i++) {
//     	final_list.push_back()
//     }
//     int index = self->obj->randint(0, size);

//     PyObject* item = PyList_GetItem(lst, index);

//     Py_INCREF(item);

//     return item;
// }

static PyMethodDef py_Random_methods[] = {
    {"randint", (PyCFunction) py_Random_randint, METH_NOARGS, "Get random int"},
    {"choice", (PyCFunction) py_Random_choice, METH_NOARGS, "Get random element in list"},
    {NULL} /* Sentinel */
};

// Тип объекта
static PyTypeObject py_RandomType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "rand.Random", /* tp_name */
    sizeof(py_Random), /* tp_basicsize */
    0, /* tp_itemsize */
    (destructor) py_Random_dealloc, /* tp_dealloc */
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
    "Random objects", /* tp_doc */
    0, /* tp_traverse */
    0, /* tp_clear */
    0, /* tp_richcompare */
    0, /* tp_weaklistoffset */
    0, /* tp_iter */
    0, /* tp_iternext */
    py_Random_methods, /* tp_methods */
    0, /* tp_members */
    0, /* tp_getset */
    0, /* tp_base */
    0, /* tp_dict */
    0, /* tp_descr_get */
    0, /* tp_descr_set */
    0, /* tp_dictoffset */
    (initproc) py_Random_init, /* tp_init */
    0, /* tp_alloc */
    py_Random_new, /* tp_new */
};

// Модуль Python
static PyModuleDef moduleName_module = {
    PyModuleDef_HEAD_INIT,
    "rand", /* name of module */
    "Write and read files with C++ functions", /* module documentation */
    -1,
};

// Инициализация модуля
PyMODINIT_FUNC PyInit_rand(void) {
    PyObject *m;

    // Зарегистрируем тип класса
    if (PyType_Ready(&py_RandomType) < 0)
        return NULL;

    // Создаем модуль
    m = PyModule_Create(&moduleName_module);
    if (m == NULL)
        return NULL;

    // Добавляем тип класса в модуль
    Py_INCREF(&py_RandomType);
    PyModule_AddObject(m, "Random", (PyObject *) &py_RandomType);

    return m;
}