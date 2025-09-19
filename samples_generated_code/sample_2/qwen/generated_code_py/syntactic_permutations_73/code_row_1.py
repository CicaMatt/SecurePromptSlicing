import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100),
                ("age", ctypes.c_uint32)]

def allocate_person():
    return ctypes.pointer(Person())

person_ptr = allocate_person()