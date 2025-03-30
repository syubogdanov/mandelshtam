// Copyright (c) 2025 Sergei Y. Bogdanov
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define MIN_OF_THREE(a, b, c) \
  ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

#define SWAP(T, a, b) \
  do {                \
    T tmp = a;        \
    a = b;            \
    b = tmp;          \
  } while (0)

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static PyObject* c_levenshtein(PyObject* self, PyObject* args) {
  PyObject* s1 = NULL;
  PyObject* s2 = NULL;

  if (!PyArg_ParseTuple(args, "OO", &s1, &s2)) {
    return NULL;
  }

  Py_ssize_t l1 = PyObject_Length(s1);
  Py_ssize_t l2 = PyObject_Length(s2);

  if (l1 == 0) {
    /* Returns 'NULL' on errors */
    return PyLong_FromSsize_t(l2);
  }

  if (l2 == 0) {
    /* Returns 'NULL' on errors */
    return PyLong_FromSsize_t(l1);
  }

  if (l1 > l2) {
    SWAP(PyObject*, s1, s2);
    SWAP(Py_ssize_t, l1, l2);
  }

  size_t* m1 = (size_t*)malloc((l1 + 1) * sizeof(size_t));
  size_t* m2 = (size_t*)malloc((l1 + 1) * sizeof(size_t));

  if (!m1 || !m2) {
    free(m1);
    free(m2);
    PyErr_NoMemory();
    return NULL;
  }

  for (Py_ssize_t i2 = 0; i2 <= l2; i2++) {
    m1[i2] = i2;
  }

  PyObject* v1 = NULL;
  PyObject* v2 = NULL;

  for (Py_ssize_t i2 = 0; i2 < l2; i2++) {
    m2[0] = i2 + 1;

    /* Returns 'NULL' on errors */
    v2 = PySequence_GetItem(s2, i2);

    if (!v2) {
      free(m1);
      free(m2);
      return NULL;
    }

    for (Py_ssize_t i1 = 0; i1 < l1; i1++) {
      /* Returns 'NULL' on errors */
      v1 = PySequence_GetItem(s1, i1);

      if (!v1) {
        free(m1);
        free(m2);
        Py_DECREF(v2);
        return NULL;
      }

      /* Returns '-1' on errors - be careful with '!is_substitutable' */
      int is_substitutable = PyObject_RichCompareBool(v1, v2, Py_EQ);

      Py_DECREF(v1);

      if (is_substitutable < 0) {
        free(m1);
        free(m2);
        Py_DECREF(v2);
        return NULL;
      }

      size_t c1 = m1[i1 + 1] + 1;
      size_t c2 = m2[i1] + 1;
      size_t c3 = m1[i1] + ((is_substitutable == 1) ? 0 : 1);

      m2[i1 + 1] = MIN_OF_THREE(c1, c2, c3);
    }

    Py_DECREF(v2);

    SWAP(size_t*, m1, m2);
  }

  size_t distance = m1[l1];

  free(m1);
  free(m2);

  /* Returns 'NULL' on errors */
  return PyLong_FromSize_t(distance);
}

static PyMethodDef module_methods[] = {
    {"c_levenshtein", c_levenshtein, METH_VARARGS,
     "Calculate the Levenshtein distance."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT, "mandelshtam.internal.levenshtein.internal.clang",
    NULL, -1, module_methods};

PyMODINIT_FUNC PyInit_clang(void) { return PyModule_Create(&module_def); }
