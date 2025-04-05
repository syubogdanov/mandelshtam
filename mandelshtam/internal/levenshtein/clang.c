// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Sergei Y. Bogdanov

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef SWAP
#define SWAP(a, b)      \
  {                     \
    typeof(a) _tmp = a; \
    a = b;              \
    b = _tmp;           \
  }
#endif

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

  wchar_t* w1 = PyUnicode_AsWideCharString(u1, &l1);
  wchar_t* w2 = PyUnicode_AsWideCharString(u2, &l2);

  if (!w1 || !w2) {
    PyMem_Free(w1);
    PyMem_Free(w2);
    return NULL;
  }

  /* Release the GIL - Python will not be used */
  PyThreadState* thread = PyEval_SaveThread();

  if (l1 > l2) {
    SWAP(w1, w2);
    SWAP(l1, l2);
  }

  wchar_t* s1 = w1;
  wchar_t* s2 = w2;

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

    PyMem_Free(w1);
    PyMem_Free(w2);

    return PyLong_FromSsize_t(l2);
  }

  if (l2 == 0) {
    /* Acquire the GIL again */
    PyEval_RestoreThread(thread);

    PyMem_Free(w1);
    PyMem_Free(w2);

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

    PyMem_Free(w1);
    PyMem_Free(w2);

    PyErr_NoMemory();
    return NULL;
  }

  for (Py_ssize_t i1 = 0; i1 <= l1; i1++) {
    m1[i1] = i1;
  }

  for (Py_ssize_t i2 = 0; i2 < l2; i2++) {
    m2[0] = i2 + 1;

    for (Py_ssize_t i1 = 0; i1 < l1; i1++) {
      size_t insertOrDelete = MIN(m1[i1 + 1], m2[i1]) + 1;
      size_t maybeEdit = m1[i1] + (size_t)(s1[i1] != s2[i2]);
      m2[i1 + 1] = MIN(insertOrDelete, maybeEdit);
    }

    SWAP(m1, m2);
  }

  size_t distance = m1[l1];

  free(m1);
  free(m2);

  /* Acquire the GIL again */
  PyEval_RestoreThread(thread);

  PyMem_Free(w1);
  PyMem_Free(w2);

  return PyLong_FromSize_t(distance);
}

static PyMethodDef module_methods[] = {
    {"c_levenshtein", c_levenshtein, METH_VARARGS,
     "Calculate the Levenshtein distance."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT, "mandelshtam.internal.levenshtein.clang", NULL, -1,
    module_methods};

PyMODINIT_FUNC PyInit_clang(void) { return PyModule_Create(&module_def); }
