import ctypes

class Person:
    def __init__(self):
        self.name = "John"
        self.status = 0

def allocate_memory(size):
    buffer = (ctypes.c_char * size)()
    person = Person()
    ctypes.memmove(buffer, bytes(ctypes.addressof(ctypes.py_object(person))), ctypes.sizeof(ctypes.c_void_p))
    return buffer

size = ctypes.sizeof(ctypes.py_object)
memory_block = allocate_memory(size)