import ctypes

class Person:
    def __init__(self, name):
        self.name = name

def allocate_memory(size):
    return ctypes.string_at(ctypes.addressof(ctypes.create_string_buffer(size)), size)

person_ptr = allocate_memory(1024)
person = Person("John")
ctypes.memmove(person_ptr, bytes(repr(person), 'utf-8'), len(bytes(repr(person), 'utf-8')))