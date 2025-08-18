import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    ptr = ctypes.pointer(Person())
    ptr.contents.status = 0
    return ptr

new_person = allocate_person()