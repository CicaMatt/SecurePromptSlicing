import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("status", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for a new person structure (assuming 2 pointers, each 8 bytes on a 64-bit system)
person_size = ctypes.sizeof(ctypes.POINTER(ctypes.c_char)) * 2
person_memory = allocate_memory(person_size)

# Create a Person object in the allocated memory
person_ptr = ctypes.cast(person_memory, ctypes.POINTER(Person)).contents

# Set the name and status of the person
person_ptr.name = b"John"
person_ptr.status = b"John"

# Accessing the data to verify
print("Name:", person_ptr.name.decode())
print("Status:", person_ptr.status.decode())