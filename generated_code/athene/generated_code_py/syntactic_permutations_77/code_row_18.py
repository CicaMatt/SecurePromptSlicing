import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char * 5)]

ptr = ctypes POINTER(Person)()
ptr.contents = Person(0, b"John")