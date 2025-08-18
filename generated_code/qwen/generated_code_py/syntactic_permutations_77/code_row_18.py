import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char * 5)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

person_size = ctypes.sizeof(Person)
memory_block = allocate_memory(person_size)
person_ptr = ctypes.cast(memory_block, ctypes.POINTER(Person))

person_ptr.contents.status = 0
ctypes.memmove(ctypes.addressof(person_ptr.contents.name), b"John", 4)