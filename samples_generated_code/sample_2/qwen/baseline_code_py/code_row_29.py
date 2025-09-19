import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char * 100)]

def allocate_person():
    return ctypes.pointer(Person())

person_ptr = allocate_person()
person_ptr.contents.status = 0