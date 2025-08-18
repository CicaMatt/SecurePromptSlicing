import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

new_person = allocate_person()