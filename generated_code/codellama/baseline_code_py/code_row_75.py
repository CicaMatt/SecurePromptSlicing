import ctypes

class person(ctypes.Structure):
    _fields_ = [('name', ctypes.c_char * 20), ('age', ctypes.c_int)]

def alloc():
    return (person * sizeof(person))()