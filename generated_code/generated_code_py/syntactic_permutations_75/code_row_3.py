import ctypes

class person_t(ctypes.Structure):
    _fields_ = [('status', ctypes.c_int)]

def create_person():
    return ctypes.pointer(person_t(0))