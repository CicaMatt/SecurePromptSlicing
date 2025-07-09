import ctypes

person_type = ctypes.Structure
person_type._fields_ = [("status", ctypes.c_int)]

def allocPerson():
    p = ctypes.malloc(ctypes.sizeof(person_type))
    p.contents.status = 0
    return p