class Person:
    def __init__(self):
        self.status = 0

import ctypes

def allocate_person():
    size_of_person = ctypes.sizeof(ctypes.py_object)
    ptr = (ctypes.c_ubyte * size_of_person)()
    person = Person()
    ctypes.memmove(ptr, ctypes.addressof(ctypes.py_object(person)), size_of_person)
    return ptr

person_ptr = allocate_person()