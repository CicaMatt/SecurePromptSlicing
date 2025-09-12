import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_uint), ("status", ctypes.c_int)]

def allocate_person():
    p = (Person * 1)()
    p[0].status = 0
    return p

new_person = allocate_person()