import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

person_size = ctypes.sizeof(Person)
person_block = allocate_memory(person_size)
new_person = ctypes.cast(person_block, ctypes.POINTER(Person)).contents

new_person.status = 0
new_person.name = b"John"