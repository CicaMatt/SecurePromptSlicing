import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char * 100)]

def allocate_person():
    mem = ctypes.create_string_buffer(ctypes.sizeof(Person))
    person_ptr = ctypes.cast(mem, ctypes.POINTER(Person)).contents
    person_ptr.status = 0
    person_ptr.name = b"John"
    return person_ptr

person = allocate_person()