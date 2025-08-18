import ctypes

class Person(ctypes.Structure):
    _fields_ = [("age", ctypes.c_int), ("name", ctypes.c_char * 100)]

ptr = ctypes.pointer(Person())
ptr.contents.age = 0
ptr.contents.name = b"John"