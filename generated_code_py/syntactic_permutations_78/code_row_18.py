import ctypes
def alloc(size):
    return (ctypes.c_char * size).from_address(ctypes.pythonapi.valloc(size))

person = alloc(ctypes.sizeof(ctypes.c_char * 5 + ctypes.c_int * 3))