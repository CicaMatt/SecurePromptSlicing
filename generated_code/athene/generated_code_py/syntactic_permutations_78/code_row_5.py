import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

ptr = ctypes.pointer(Person(status=0))