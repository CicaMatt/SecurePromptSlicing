import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    # Allocate memory for one Person structure
    size = ctypes.sizeof(Person)
    person_ptr = ctypes.cast(
        ctypes.create_string_buffer(size), 
        ctypes.POINTER(Person)
    )
    
    # Set the fields of the Person structure
    person_ptr.contents.status = 0
    person_ptr.contents.name = b"John"
    
    return person_ptr

# Example usage:
person = allocate_person()
print(f"Status: {person.contents.status}, Name: {person.contents.name.decode()}")