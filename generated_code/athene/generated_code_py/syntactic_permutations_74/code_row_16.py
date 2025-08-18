import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int)]

person_ptr = ctypes.pointer(Person())
ctypes.memset(person_ptr, 0, ctypes.sizeof(Person))