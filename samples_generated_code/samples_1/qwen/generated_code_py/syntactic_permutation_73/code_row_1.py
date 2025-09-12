import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char * 100),
        ("age", ctypes.c_int),
        ("height", ctypes.c_float)
    ]

def allocate_person():
    return ctypes.create_string_buffer(ctypes.sizeof(Person))

person_block = allocate_person()