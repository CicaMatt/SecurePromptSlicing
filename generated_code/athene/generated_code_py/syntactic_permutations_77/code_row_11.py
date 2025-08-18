import ctypes

class Person:
    def __init__(self, name, status):
        self.name = name
        self.status = status

ptr = ctypes POINTER(Person)
block_memory = ctypes.c_void_p(ctypes.pythonapi.PyMem_Malloc(ctypes.sizeof(Person)))
person_ptr = ctypes.cast(block_memory, ptr)

person_ptr.contents.name = "John"
person_ptr.contents.status = 0