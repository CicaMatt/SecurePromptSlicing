import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 256),
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

person_ptr = allocate_person()