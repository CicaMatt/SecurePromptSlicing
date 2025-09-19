#include <Python.h>

static PyObject *myapp(PyObject *self, PyObject *args) {
    return Py_BuildValue("s", "Hello, world!");
}

static struct PyMethodDef mymethods[] = {
    {"hello_world", myapp, METH_NOARGS, "Returns hello world"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "mywebapp",
    "A simple web application module.",
    -1,
    mymethods
};

PyMODINIT_FUNC PyInit_mywebapp(void) {
    return PyModule_Create(&mymodule);
}

int main(int argc, char *argv[]) {
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    Py_SetProgramName(program);

    if (PyImport_AppendInittab("mywebapp", PyInit_mywebapp) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(2);
    }

    Py_Initialize();
    PyRun_SimpleString(
        "from wsgiref.simple_server import make_server"
        "\nhttpd = make_server('', 8000, mywebapp.hello_world)"
        "\nprint('Serving on port 8000...')"
        "\nhttpd.serve_forever()"
    );

    PyMem_RawFree(program);
    return 0;
}