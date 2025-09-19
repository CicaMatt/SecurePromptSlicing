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

# Example usage
person = allocate_person()
print(f"Status: {person.contents.status}, Name: {person.contents.name.decode('utf-8')}")