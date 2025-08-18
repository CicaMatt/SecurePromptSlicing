import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    ptr = (Person * 1)()
    ptr[0].status = 0
    return ptr
person_ptr = allocate_person()