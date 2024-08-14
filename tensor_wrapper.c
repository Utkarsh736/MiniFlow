#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "minitensor.h"

// Function to create a tensor
static PyObject* py_create_tensor(PyObject* self, PyObject* args) {
    size_t size;
    if (!PyArg_ParseTuple(args, "n", &size)) {
        return NULL;
    }
    Tensor* tensor = create_tensor(size);
    return Py_BuildValue("n", (size_t)tensor); // Return pointer as integer
}

// Function to view a tensor
static PyObject* py_view_tensor(PyObject* self, PyObject* args) {
    size_t new_size;
    size_t tensor_ptr;
    if (!PyArg_ParseTuple(args, "nn", &tensor_ptr, &new_size)) {
        return NULL;
    }
    Tensor* tensor = (Tensor*)tensor_ptr; // Cast back to Tensor pointer
    Tensor* new_tensor = view_tensor(tensor, new_size);
    return Py_BuildValue("n", (size_t)new_tensor); // Return a new tensor pointer
}

// Function to free a tensor
static PyObject* py_free_tensor(PyObject* self, PyObject* args) {
    size_t tensor_ptr;
    if (!PyArg_ParseTuple(args, "n", &tensor_ptr)) {
        return NULL;
    }
    Tensor* tensor = (Tensor*)tensor_ptr;
    free_tensor(tensor);
    Py_RETURN_NONE;
}

// Method definitions
static PyMethodDef TensorMethods[] = {
    {"create_tensor", py_create_tensor, METH_VARARGS, "Create a new tensor."},
    {"view_tensor", py_view_tensor, METH_VARARGS, "View a tensor"},
    {"free_tensor", py_free_tensor, METH_VARARGS, "Free a tensor"},
    {NULL, NULL, 0, NULL} //Sentinel
};

// Module definition
static struct PyModuleDef tensormodule = {
    PyModuleDef_HEAD_INIT,
    "tensor", // Module name
    NULL, //Module documentation
    -1, // Size of per-interpreter state of the module
    TensorMethods // Method definitions
};

// Module initialization
PyMODINIT_FUNC PyInit_tensor(void) {
    return PyModule_Create(&tensormodule);
}