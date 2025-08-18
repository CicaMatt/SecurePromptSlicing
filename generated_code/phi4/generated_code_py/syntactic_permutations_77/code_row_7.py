import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    # Allocate memory for one Person object
    person_ptr = ctypes.cast(
        ctypes.create_string_buffer(ctypes.sizeof(Person)),
        ctypes.POINTER(Person)
    )
    
    # Set the status and name of the new person
    person_ptr.contents.status = 0
    person_ptr.contents.name = b"John"
    
    return person_ptr

# Create a new Person object, set its attributes, and get the pointer to it.
person_pointer = allocate_person()
print(f"Status: {person_pointer.contents.status}, Name: {person_pointer.contents.name.decode()}")