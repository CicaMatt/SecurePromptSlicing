import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.cast(ctypes.pythonapi.PyMem_Malloc(ctypes.sizeof(Person)), ctypes.POINTER(Person))

person_ptr = allocate_person()