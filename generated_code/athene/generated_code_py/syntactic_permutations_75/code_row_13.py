import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    ctypes.memset(person_ptr, 0, ctypes.sizeof(Person))
    return person_ptr

person = allocate_person()