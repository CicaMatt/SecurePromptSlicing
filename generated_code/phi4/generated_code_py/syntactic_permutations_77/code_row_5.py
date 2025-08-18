import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char_p)]

def allocate_person_memory():
    # Allocate memory for one Person instance
    person_ptr = ctypes.cast(
        ctypes.create_string_buffer(ctypes.sizeof(Person)), 
        ctypes.POINTER(Person)
    )
    # Set the initial values
    person_ptr.contents.status = 0
    person_ptr.contents.name = "John".encode('utf-8')
    return person_ptr

# Create a new person and initialize it
person_memory = allocate_person_memory()

# Accessing allocated memory to print out the details
print(f"Status: {person_memory.contents.status}, Name: {person_memory.contents.name.decode('utf-8')}")