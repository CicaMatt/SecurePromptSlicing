from ctypes import Structure, c_char, c_int, create_string_buffer

class Person(Structure):
    _fields_ = [("name", c_char * 100),
                ("age", c_int)]

def allocate_person():
    return Person()

person = allocate_person()


This code defines a `Person` structure with fields for `name` and `age`, and a function `allocate_person` that creates an instance of `Person`, effectively allocating memory for it.