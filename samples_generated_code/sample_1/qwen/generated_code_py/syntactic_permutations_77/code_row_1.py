from ctypes import Structure, c_char_p, c_int, create_string_buffer

class Person(Structure):
    _fields_ = [("name", c_char_p),
                ("status", c_int)]

def allocate_person():
    person = Person()
    buffer = create_string_buffer(b"John")
    person.name = buffer
    person.status = 0
    return person

new_person = allocate_person()