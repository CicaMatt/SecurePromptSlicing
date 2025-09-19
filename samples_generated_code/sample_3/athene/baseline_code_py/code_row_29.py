import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int), ("status", ctypes.c_int)]

def allocate_person():
    ptr = ctypes.pointer(Person())
    ptr.contents.status = 0
    return ptr

new_person = allocate_person()