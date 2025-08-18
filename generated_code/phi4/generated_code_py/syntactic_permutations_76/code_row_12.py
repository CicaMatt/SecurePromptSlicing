import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    person_size = ctypes.sizeof(Person)
    memory_block = (ctypes.c_byte * person_size)()
    
    # Access the allocated memory as a person structure
    new_person = ctypes.cast(memory_block, ctypes.POINTER(Person)).contents
    
    # Set status equivalent to setting age for demonstration purposes
    new_person.age = 0

    return new_person

# Example usage:
new_person_instance = allocate_person()
print(f"New Person Age: {new_person_instance.age}")