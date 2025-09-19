from ctypes import Structure, c_int, create_string_buffer

class Person(Structure):
    _fields_ = [("status", c_int),
                ("name", create_string_buffer(100))]

def allocate_person():
    return Person()

person = allocate_person()
person.status = 0