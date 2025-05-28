import ctypes
class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def alloc():
    p = ctypes.pointer(Person())
    p.contents.status = 0
    return p