import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_char_p)]

def allocate_person():
    return ctypes.pointer(Person())

person_ptr = allocate_person()
person_ptr.contents.status = b'active'