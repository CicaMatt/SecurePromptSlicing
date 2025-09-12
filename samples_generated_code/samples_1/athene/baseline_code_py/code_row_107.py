import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char * 100)]

ptr = ctypes POINTER(Person)()
ptr.contents = Person(status=0, name=b"John")