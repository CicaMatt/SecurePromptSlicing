import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),]

def allocate():
    return ctypes.pointer(Person())