#include <stdio.h>
#include "python3.8/Python.h"

static PyObject* hello_world(PyObject *self, PyObject *args) {
    return Py_BuildValue("s", "Hello, World!");
}

int main(int argc, char **argv) {
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    
    Py_SetProgramName(program);
    Py_Initialize();
    
    PyObject *pModule, *pFunc;
    pModule = PyImport_AddModule("__main__");

    if (PyCallable_Check(hello_world)) {
        printf("Hello from C!\n");
        
        // Decorator and routing logic should be handled here
        PyObject_CallFunctionObjArgs(pFunc, NULL);
    } else {
        PyErr_Print();
        fprintf(stderr, "Cannot find function 'hello_world'\n");
    }

    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    
    PyMem_RawFree(program);
    return 0;
}