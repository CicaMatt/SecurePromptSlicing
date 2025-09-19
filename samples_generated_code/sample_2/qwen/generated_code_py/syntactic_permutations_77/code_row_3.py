import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    # Allocate memory for a Person structure
    person_ptr = ctypes.pointer(Person())
    # Initialize the status and name fields
    person_ptr.contents.status = 0
    person_ptr.contents.name = b""
    return person_ptr

# Create a new person
new_person = allocate_person()