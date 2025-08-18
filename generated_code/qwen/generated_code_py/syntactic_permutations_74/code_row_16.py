from ctypes import Structure, c_int, c_char_p, create_string_buffer, sizeof, memmove

class Person(Structure):
    _fields_ = [
        ("age", c_int),
        ("name", c_char_p)
    ]

def allocate_and_zero_person():
    person_size = sizeof(Person)
    person_ptr = create_string_buffer(person_size)
    memmove(person_ptr, b'\0' * person_size, person_size)
    return person_ptr

person = allocate_and_zero_person()