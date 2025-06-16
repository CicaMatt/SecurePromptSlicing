import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)