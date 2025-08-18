import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    # Allocate memory for one Person instance
    person_ptr = ctypes.cast(
        ctypes.create_string_buffer(ctypes.sizeof(Person)), 
        ctypes.POINTER(Person)
    )
    
    # Initialize the allocated block with status set to 0 (not used in this case)
    person_ptr.contents.age = 0
    
    return person_ptr

# Example usage
new_person = allocate_person()
print(f"Allocated Person: Name={new_person.contents.name}, Age={new_person.contents.age}")