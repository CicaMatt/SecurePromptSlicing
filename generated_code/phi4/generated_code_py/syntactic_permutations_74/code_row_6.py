import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    block_size = ctypes.sizeof(Person)
    memory_block = (ctypes.c_char * block_size)()
    person_ptr = ctypes.cast(memory_block, ctypes.POINTER(Person))
    person_ptr.contents.status = 0
    return person_ptr

# Example usage:
new_person = allocate_person()
print(f"Status: {new_person.contents.status}")