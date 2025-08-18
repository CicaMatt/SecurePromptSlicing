import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 50), ("age", ctypes.c_int)]

def allocate_person():
    ptr = (Person * 1)()
    ctypes.memset(ctypes.addressof(ptr.contents), 0, ctypes.sizeof(Person))
    return ptr

person_ptr = allocate_person()