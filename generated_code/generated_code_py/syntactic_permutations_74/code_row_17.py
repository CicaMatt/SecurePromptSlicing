import ctypes
import os

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

def alloc():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))