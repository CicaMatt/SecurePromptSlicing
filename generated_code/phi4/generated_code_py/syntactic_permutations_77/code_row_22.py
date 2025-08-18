import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for a Person structure
person_size = ctypes.sizeof(Person)
memory_block = allocate_memory(person_size)

# Create a new person in the allocated memory
new_person = ctypes.cast(memory_block, ctypes.POINTER(Person)).contents

# Set status and name of the person
new_person.status = 1  # Example status
new_person.name = b"John"

# Accessing the person's data for demonstration purposes
print(f"Status: {new_person.status}, Name: {new_person.name.decode('utf-8')}")