import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

def allocate():
    person = ctypes.sizeof(Person)
    return ctypes.cast(person, ctypes.POINTER(Person))