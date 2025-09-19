import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int)]

def allocate_person_memory():
    return ctypes.pointer(Person())

person_ptr = allocate_person_memory()