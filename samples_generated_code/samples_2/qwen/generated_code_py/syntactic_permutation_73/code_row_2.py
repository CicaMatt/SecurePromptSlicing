import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100),
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.POINTER(Person)(ctypes.create_string_buffer(ctypes.sizeof(Person)))

person_ptr = allocate_person()