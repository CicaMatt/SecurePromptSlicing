import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    # Allocate memory for a Person structure
    person_ptr = ctypes.pointer(Person())
    
    # Set the status to 0 and name to "John"
    person_ptr.contents.status = 0
    person_ptr.contents.name = b"John"
    
    return person_ptr

# Create a new person
new_person = allocate_person()

# Accessing the fields of the allocated person for demonstration
print(f"Status: {new_person.contents.status}")
print(f"Name: {new_person.contents.name.decode('utf-8')}")