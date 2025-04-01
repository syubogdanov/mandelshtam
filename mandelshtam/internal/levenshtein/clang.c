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
  PyObject* u1 = NULL;
  PyObject* u2 = NULL;

  if (!PyArg_ParseTuple(args, "UU", &u1, &u2)) {
    return NULL;
  }

  Py_ssize_t l1 = 0;
  Py_ssize_t l2 = 0;

  const char* s1 = PyUnicode_AsUTF8AndSize(u1, &l1);
  const char* s2 = PyUnicode_AsUTF8AndSize(u2, &l2);

  if (!s2 || !s2) {
    return NULL;
  }

  /* Release the GIL - Python will not be used */
  PyThreadState* thread = PyEval_SaveThread();

  if (l1 > l2) {
    SWAP(const char*, s1, s2);
    SWAP(Py_ssize_t, l1, l2);
  }

  /* Strip the common prefix */
  while (l1 > 0 && *s1 == *s2) {
    --l1;
    --l2;
    ++s1;
    ++s2;
  }

  /* Strip the common suffix */
  while (l1 > 0 && s1[l1 - 1] == s2[l2 - 1]) {
    --l1;
    --l2;
  }

  if (l1 == 0) {
    /* Acquire the GIL again */
    PyEval_RestoreThread(thread);
    return PyLong_FromSsize_t(l2);
  }

  if (l2 == 0) {
    /* Acquire the GIL again */
    PyEval_RestoreThread(thread);
    return PyLong_FromSsize_t(l1);
  }

  /* Do not use a single buffer to avoid overflow */
  size_t* m1 = (size_t*)malloc((l1 + 1) * sizeof(size_t));
  size_t* m2 = (size_t*)malloc((l1 + 1) * sizeof(size_t));

  if (!m1 || !m2) {
    free(m1);
    free(m2);

    /* Acquire the GIL again */
    PyEval_RestoreThread(thread);

    PyErr_NoMemory();
    return NULL;
  }

  for (Py_ssize_t i2 = 0; i2 <= l2; i2++) {
    m1[i2] = i2;
  }

  for (Py_ssize_t i2 = 0; i2 < l2; i2++) {
    m2[0] = i2 + 1;

    for (Py_ssize_t i1 = 0; i1 < l1; i1++) {
      size_t c1 = m1[i1 + 1] + 1;
      size_t c2 = m2[i1] + 1;
      size_t c3 = m1[i1] + (size_t)(s1[i1] != s2[i2]);
      m2[i1 + 1] = MIN_OF_THREE(c1, c2, c3);
    }

    SWAP(size_t*, m1, m2);
  }

  size_t distance = m1[l1];

  free(m1);
  free(m2);

  /* Acquire the GIL again */
  PyEval_RestoreThread(thread);

  return PyLong_FromSize_t(distance);
}

static PyMethodDef module_methods[] = {
    {"c_levenshtein", c_levenshtein, METH_VARARGS,
     "Calculate the Levenshtein distance."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT, "mandelshtam.internal.levenshtein.clang", NULL,
    -1, module_methods};

PyMODINIT_FUNC PyInit_clang(void) { return PyModule_Create(&module_def); }
