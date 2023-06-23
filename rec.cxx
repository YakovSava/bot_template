# include <Python.h>
# include <iostream>
# include <vector>
# include <unordered_map>
# include <algorithm>
using namespace std;

vector<int> func(vector<int> lst) {
    // Создаем словарь, где ключ - это уникальные числа из списка, а значение - количество их повторений в списке
    unordered_map<int, int> count_map;
    for (const auto& num : lst) {
        count_map[num]++;
    }
    
    // Сортируем уникальные числа по убыванию количества их повторений в списке
    sort(lst.begin(), lst.end(), [&count_map](int a, int b) {
        return count_map[a] > count_map[b];
    });
    
    // Возвращаем отсортированный список
    return lst;
}

PyObject* sorting_by_frequency(PyObject* self, PyObject* args) {
    PyObject* lst_obj;
    if (!PyArg_ParseTuple(args, "O", &lst_obj)) {
        return NULL;
    }

    // Преобразование списка Python в вектор C++
    vector<int> vec_old;
    Py_ssize_t size = PyList_Size(lst_obj);
    for (Py_ssize_t i = 0; i < size; i++) {
        PyObject* num_obj = PyList_GetItem(lst_obj, i);
        int num = PyLong_AsLong(num_obj);
        vec_old.push_back(num);
    }

    vector<int> vec = func(vec_old);

    PyObject* result_obj = PyList_New(size);
    for (Py_ssize_t i = 0; i < size; i++) {
        int num = vec[i];
        PyObject* num_obj = PyLong_FromLong(num);
        PyList_SetItem(result_obj, i, num_obj);
    }

    return result_obj;
}

static PyMethodDef methods[] = {
    {"sorting_by_frequency", sorting_by_frequency, METH_VARARGS, "Implementation of frequency sorting in C++"},
    {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "rec",
    "Recomendate for you!",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_rec(void) {
    return PyModule_Create(&module);
}