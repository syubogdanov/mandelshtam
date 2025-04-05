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
#include <stdbool.h>
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

  size_t* previousRow = (size_t*)calloc(l1, sizeof(size_t));

  if (!previousRow) {
    /* Acquire the GIL again */
    PyEval_RestoreThread(thread);

    PyMem_Free(w1);
    PyMem_Free(w2);

    PyErr_NoMemory();
    return NULL;
  }

  for (Py_ssize_t i1 = 0; i1 < l1; ++i1) {
    previousRow[i1] = i1 + 1;
  }

  for (Py_ssize_t i2 = 0; i2 < l2; ++i2) {
    size_t diagonalDistance = i2;
    size_t leftDistance = i2 + 1;

    for (Py_ssize_t i1 = 0; i1 < l1; ++i1) {
      size_t upperDistance = previousRow[i1];

      bool isEditable = (s1[i1] != s2[i2]);
      size_t maybeEdit = diagonalDistance + isEditable;
      size_t insertOrDelete = MIN(leftDistance, upperDistance) + 1;

      leftDistance = MIN(insertOrDelete, maybeEdit);

      diagonalDistance = upperDistance;
      previousRow[i1] = leftDistance;
    }
  }

  size_t distance = previousRow[l1 - 1];

  free(previousRow);

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
