#include <Python.h>

static PyObject* hello(PyObject *self, PyObject *args) {
    return Py_BuildValue("s", "Hello, World!");
}

static struct PyMethodDef WebAppMethods[] = {
    {"hello", hello, METH_NOARGS, "Returns a greeting message."},
    {NULL, NULL, 0, NULL}
};

static int web_application_init(web_application_module *self, PyObject *args) {
    // Initialize the WSGI application
    return 0;
}

static PyModuleDef WebAppModule = {
    PyModuleDef_HEAD_INIT,
    "web_application",
    NULL,
    -1,
    WebAppMethods
};

PyMODINIT_FUNC PyInit_web_application(void) {
    PyObject* m;
    if (PyType_Ready(&WebAppModule) < 0)
        return NULL;

    m = PyModule_Create(&WebAppModule);
    if (m == NULL)
        return NULL;

    return m;
}

int main(int argc, char *argv[]) {
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    Py_SetProgramName(program);
    Py_Initialize();
    PyImport_AppendInittab("web_application", &PyInit_web_application);

    PyObject *pModule = PyImport_ImportModule("web_application");

    if (pModule != NULL) {
        PyObject_CallMethod(pModule, "hello", NULL);
    }

    if (Py_FinalizeEx() < 0) {
        exit(120);
    }

    PyMem_RawFree(program);

    return 0;
}