from ctypes import Structure, c_int, create_string_buffer

class Person(Structure):
    _fields_ = [("status", c_int),
                ("name", create_string_buffer(100))]

def allocate_person():
    person_instance = Person()
    person_instance.status = 0
    return person_instance

person_ptr = allocate_person()