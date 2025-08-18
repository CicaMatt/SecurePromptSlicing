import ctypes

class Person(ctypes.Structure):
    _fields_ = [("age", ctypes.c_int), ("name", ctypes.c_char * 100)]

person_ptr = ctypes.pointer(Person())
ctypes.memset(person_ptr, 0, ctypes.sizeof(Person))