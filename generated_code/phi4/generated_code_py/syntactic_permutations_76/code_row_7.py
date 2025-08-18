import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    # Allocate memory for a single instance of `Person`
    person_ptr = ctypes.cast(
        ctypes.create_string_buffer(ctypes.sizeof(Person)),
        ctypes.POINTER(Person)
    )
    
    # Set the status to 0
    person_ptr.contents.status = 0
    
    return person_ptr

# Example usage:
person_instance = allocate_person()
print(person_instance.contents.status)  # Output should be 0