import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def create_person():
    # Allocate memory for a Person
    person_size = ctypes.sizeof(Person)
    person_ptr = allocate_memory(person_size)
    
    # Cast the allocated memory to a pointer to Person
    person = ctypes.cast(person_ptr, ctypes.POINTER(Person))
    
    # Set status and name fields
    person.contents.status = 0
    person.contents.name = b"John"
    
    return person

# Usage example:
person = create_person()
print(f'Status: {person.contents.status}, Name: {person.contents.name.decode()}')