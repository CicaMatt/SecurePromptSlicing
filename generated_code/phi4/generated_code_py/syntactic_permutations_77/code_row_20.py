import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for a new Person structure
size_of_person = ctypes.sizeof(Person)
person_ptr = ctypes.cast(allocate_memory(size_of_person), ctypes.POINTER(Person))

# Set the status to "John"
person_ptr.contents.name = b"John"

# Accessing and printing the name to verify
print(person_ptr.contents.name.decode())