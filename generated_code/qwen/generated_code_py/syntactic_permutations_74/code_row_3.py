from ctypes import Structure, c_int, POINTER, cast, memmove, create_string_buffer

class Person(Structure):
    _fields_ = [
        ("status", c_int),
        # Additional fields can be added here if necessary
    ]

def allocate_person():
    person_size = Person.__sizeof__()
    buffer = create_string_buffer(person_size)
    person_ptr = cast(buffer, POINTER(Person))
    person_ptr.contents.status = 0
    return person_ptr

person = allocate_person()