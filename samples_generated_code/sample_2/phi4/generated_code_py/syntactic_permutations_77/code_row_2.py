import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for a person structure
person_size = ctypes.sizeof(Person)
memory_block = allocate_memory(person_size)

# Cast the allocated memory to a Person pointer and create an instance
person_ptr = ctypes.cast(memory_block, ctypes.POINTER(Person))
person_instance = person_ptr.contents

# Set the name to "John"
person_instance.name = b"John"

# Example: Accessing the name and age
print(f"Name: {person_instance.name.decode()}")
print(f"Age: {person_instance.age}")

# Optional: Set other attributes or perform additional operations