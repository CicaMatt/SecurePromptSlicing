import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    # Allocate memory for one instance of `Person`
    person_ptr = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    
    # Initialize the new Person's status to 0
    person_instance = person_ptr.contents
    person_instance.status = 0
    
    return person_ptr

# Example usage:
person_memory = allocate_person()
print(f"Status: {person_memory.contents.status}")