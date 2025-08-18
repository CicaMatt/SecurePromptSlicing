import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    # Allocate memory for one instance of 'Person'
    p = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    # Set the status to 0
    p.contents.status = 0
    return p

# Example usage:
person_ptr = allocate_person()
print(person_ptr.contents.status)  # Output: 0