import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int), ("status", ctypes.c_int)]

def allocate_person():
    ptr = ctypes.POINTER(Person)()
    ptr.contents = Person(status=0)
    return ptr

person_ptr = allocate_person()