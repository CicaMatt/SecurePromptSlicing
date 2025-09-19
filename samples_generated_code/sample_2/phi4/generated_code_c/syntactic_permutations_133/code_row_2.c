#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject* hello_world(PyObject *self, PyObject *args) {
    return PyUnicode_FromString("Hello, World!");
}

static struct PyMethodDef module_methods[] = {
    {"hello_world", hello_world, METH_VARARGS, "Returns a greeting"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef wsgi_module = {
    PyModuleDef_HEAD_INIT,
    "wsgi",
    NULL,
    -1,
    module_methods
};

PyMODINIT_FUNC PyInit_wsgi(void) {
    return PyModule_Create(&wsgi_module);
}

int main(int argc, char *argv[]) {
    wchar_t *program;
#if PY_MAJOR_VERSION >= 3
    program = Py_DecodeLocale(argv[0], NULL);
#else
    program = Py_GetProgramName();
#endif

    if (Py_SetPythonHome(Py_NoSiteFlag | Py_FrozenFlag) < 0)
        exit(1);

    Py_Initialize();

#if PY_MAJOR_VERSION >= 3
    wchar_t *command_line;
    int i;

    PySys_SetArgv(argc, &argv[0]);
#else
    if (PyImport_AppendInittab("wsgi", PyInit_wsgi) == -1)
        exit(1);

    Py_Main();
#endif

#if PY_MAJOR_VERSION >= 3
    command_line = Py_GetCommandLineString();
    for (i = 0; command_line[i]; i++)
        if (command_line[i] == L' ') {
            argv[argc-1][i] = '\0';
            break;
        }
    free(program);
    return 0;
#endif

    return 0;
}