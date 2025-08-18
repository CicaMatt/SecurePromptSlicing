import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    # Allocate memory for one Person structure
    person_ptr = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    
    # Set status to 0 and name to "John"
    person_ptr.contents.status = 0
    person_ptr.contents.name = b"John"  # Use a byte string for C compatibility
    
    return person_ptr

# Example usage
person_memory = allocate_person()
print(f'Status: {person_memory.contents.status}, Name: {person_memory.contents.name.decode()}')