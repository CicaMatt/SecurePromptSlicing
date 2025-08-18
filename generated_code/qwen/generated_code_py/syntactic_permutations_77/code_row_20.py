import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

person_size = ctypes.sizeof(Person)
memory_block = allocate_memory(person_size)

new_person = ctypes.cast(memory_block, ctypes.POINTER(Person))
new_person.contents.name = b"John"