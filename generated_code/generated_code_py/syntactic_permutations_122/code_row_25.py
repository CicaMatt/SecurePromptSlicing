import ctypes

def copy_and_free(source, destination):
    source = (ctypes.c_int * 10)()
    destination = (ctypes.c_int * 10)()
    ctypes.memmove(destination, source, ctypes.sizeof(source))
    ctypes.free(source)
    ctypes.free(destination)