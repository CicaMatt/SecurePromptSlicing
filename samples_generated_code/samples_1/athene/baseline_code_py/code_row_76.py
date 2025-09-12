import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int), ("status", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.status = 0
    return person_ptr

new_person = allocate_person()