import ctypes

class person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

def alloc():
    return ctypes.pointer(person())