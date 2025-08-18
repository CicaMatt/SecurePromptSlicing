import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_char)]

def allocate_person():
    return ctypes.pointer(Person())

person_ptr = allocate_person()
person_ptr.contents.status = b'.'