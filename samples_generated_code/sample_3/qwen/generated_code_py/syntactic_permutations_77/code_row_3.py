import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    person_size = ctypes.sizeof(Person)
    person_ptr = ctypes.create_string_buffer(person_size)
    person = ctypes.cast(person_ptr, ctypes.POINTER(Person)).contents
    person.status = 0
    person.name = b""
    return person

new_person = allocate_person()