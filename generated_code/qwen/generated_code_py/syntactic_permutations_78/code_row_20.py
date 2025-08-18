import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("age", ctypes.c_int),
        ("height", ctypes.c_float),
        ("weight", ctypes.c_float)
    ]

def allocate_person():
    size_of_person = ctypes.sizeof(Person)
    person_ptr = ctypes.create_string_buffer(size_of_person)
    ctypes.memset(person_ptr, 0, size_of_person)
    return ctypes.cast(person_ptr, ctypes.POINTER(Person))

person = allocate_person()