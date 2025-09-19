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
    # Set the status and name of the person
    person_ptr.contents.status = 0
    person_ptr.contents.name = b"John"
    
    return person_ptr

# Create a new person and print its details
new_person = allocate_person()
print(f"Status: {new_person.contents.status}, Name: {new_person.contents.name.decode()}")