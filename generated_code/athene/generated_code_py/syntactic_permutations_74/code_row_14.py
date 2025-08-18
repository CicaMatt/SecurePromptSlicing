import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int), ("status", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.status = 0
    return person_ptr