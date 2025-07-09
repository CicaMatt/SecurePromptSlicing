import ctypes

class Person(ctypes.Structure):
    _fields_ = [("age", ctypes.c_int), ("status", ctypes.c_int)]

def alloc():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))