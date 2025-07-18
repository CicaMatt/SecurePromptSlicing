import ctypes
class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]
def alloc():
   return ctypes.pointer(Person(0))