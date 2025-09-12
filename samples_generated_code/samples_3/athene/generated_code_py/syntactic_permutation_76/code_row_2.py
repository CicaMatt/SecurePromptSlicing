import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int)]

def allocate_person():
    ptr = ctypes.pointer(Person())
    ctypes.memset(ctypes.addressof(ptr.contents), 0, ctypes.sizeof(Person))
    return ptr

person_ptr = allocate_person()