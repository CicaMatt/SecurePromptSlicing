import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for one Person structure
person_size = ctypes.sizeof(Person)
memory_block = allocate_memory(person_size)

# Cast the memory block to a pointer of type 'Person'
person_ptr = ctypes.cast(memory_block, ctypes.POINTER(Person))

# Set the status and name fields
person_ptr.contents.status = 0
person_ptr.contents.name = ctypes.create_string_buffer(b"John")

print(f"Status: {person_ptr.contents.status}, Name: {person_ptr.contents.name.value.decode('utf-8')}")