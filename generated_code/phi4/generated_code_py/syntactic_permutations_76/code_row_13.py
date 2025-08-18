import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    # Allocate memory for a person structure
    person_ptr = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    
    # Set the status to 0 (assuming 'status' is an attribute of Person)
    person_ptr.contents.status = 0
    
    return person_ptr

# Example usage
if __name__ == "__main__":
    person_memory = allocate_person()
    print(f"Memory allocated at address: {ctypes.addressof(person_memory.contents)}")