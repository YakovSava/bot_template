# include <Python.h>
# include <algorithm>
# include <string>
# include <vector>
using namespace std;




int Cdamerau_levenshtein_distance(string s, string t) {

    int len_s = s.length();
    int len_t = t.length();

    // Создаем вектор d с нужным размером, заполненный нулями
    vector<vector<int>> d(len_s + 1, vector<int>(len_t + 1, 0));

    for (int i = 0; i <= len_s; i++) {
        d[i][0] = i;
    }

    for (int j = 0; j <= len_t; j++) {
        d[0][j] = j;
    }

    for (int i = 1; i <= len_s; i++) {
        for (int j = 1; j <= len_t; j++) {
            int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;

            d[i][j] = min({
                d[i - 1][j] + 1,  // удаление
                d[i][j - 1] + 1,  // вставка
                d[i - 1][j - 1] + cost  // замена
            });

            if (i > 1 && j > 1 && s[i - 1] == t[j - 2] && s[i - 2] == t[j - 1]) {
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + cost);  // транспозиция
            }
        }
    }

    return d[len_s][len_t];
}




static PyObject* damerau_levenshtein_distance(PyObject* self, PyObject* args) {
    const char* s_char;
    const char* two_char;

    if (!PyArg_ParseTuple(args, "ss", &s_char, &two_char)) {
        return NULL;
    }

    int result = Cdamerau_levenshtein_distance(string(s_char), string(two_char));

    return Py_BuildValue("i", result);
}


static PyMethodDef methods[] = {
    {"damerau_levenshtein_distance", damerau_levenshtein_distance, METH_VARARGS, "Calculate damerau levenshtein distance"},
    {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "dl",
    "Damerau levenshtein distance calculator",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_dl(void) {
    return PyModule_Create(&module);
}