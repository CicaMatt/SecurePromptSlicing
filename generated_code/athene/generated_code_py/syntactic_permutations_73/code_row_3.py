import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int)]

def allocate_person_memory():
    return ctypes.POINTER(Person)().contents.__class__.from_address(ctypes.addressof((ctypes.create_string_buffer(ctypes.sizeof(Person)))))