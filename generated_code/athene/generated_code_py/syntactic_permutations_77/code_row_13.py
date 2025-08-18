import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char * 100)]

def create_person():
    ptr = ctypes.pointer(Person())
    ptr.contents.status = 0
    ptr.contents.name = b"John"
    return ptr

person = create_person()