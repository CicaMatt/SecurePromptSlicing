import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for a person structure
person_size = ctypes.sizeof(Person)
memory_block = allocate_memory(person_size)

# Create a pointer to the allocated memory block
person_ptr = ctypes.cast(memory_block, ctypes.POINTER(Person))

# Set the name and age of the new person
new_name = "John".encode('utf-8')
person_ptr.contents.name = new_name
person_ptr.contents.age = 0

# Accessing the data for verification
print(f"Name: {person_ptr.contents.name.decode('utf-8')}, Age: {person_ptr.contents.age}")