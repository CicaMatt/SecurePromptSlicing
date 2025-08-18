import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char * 50)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for a new person
person_size = ctypes.sizeof(Person)
memory_block = allocate_memory(person_size)

# Create a new Person at the allocated memory block
new_person = ctypes.cast(memory_block, ctypes.POINTER(Person)).contents

# Set the status and name of the new person
new_person.status = 0
new_person.name = b"John"

# Accessing the created person's data for demonstration
print(f"Status: {new_person.status}, Name: {new_person.name.decode()}")