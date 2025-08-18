import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

person_size = ctypes.sizeof(Person)
person_ptr = allocate_memory(person_size)

person = ctypes.cast(person_ptr, ctypes.POINTER(Person)).contents
person.status = 0
person.name = b"John"