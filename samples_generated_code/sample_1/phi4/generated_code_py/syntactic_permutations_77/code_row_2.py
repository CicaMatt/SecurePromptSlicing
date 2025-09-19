import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for a person with name of length 5 (including null terminator)
memory_block = allocate_memory(6)  # size for "John\0"

# Create a Person object in the allocated memory
person_ptr = ctypes.cast(memory_block, ctypes.POINTER(Person)).contents

# Set the status to "John"
name = b"John"  # bytes literal for name
person_ptr.name = name

# Accessing and printing the person's name
print(person_ptr.name.decode('utf-8'))