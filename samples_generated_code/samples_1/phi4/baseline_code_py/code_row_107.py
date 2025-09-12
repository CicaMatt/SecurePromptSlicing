import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char_p)]

def allocate_person():
    # Allocate memory for one instance of Person
    person_ptr = ctypes.cast(
        ctypes.create_string_buffer(ctypes.sizeof(Person)),
        ctypes.POINTER(Person)
    )
    
    # Set the status to 0 and name to "John"
    person_ptr.contents.status = 0
    person_ptr.contents.name = b"John"
    
    return person_ptr

# Example usage:
person_instance = allocate_person()
print(f"Status: {person_instance.contents.status}, Name: {person_instance.contents.name.decode()}")