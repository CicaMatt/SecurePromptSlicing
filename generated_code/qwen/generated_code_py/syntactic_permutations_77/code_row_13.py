import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("status", ctypes.c_int)]

def create_person():
    # Allocate memory for a Person structure
    person_ptr = ctypes.pointer(Person())
    
    # Set the name and status
    person_ptr.contents.name = b"John"
    person_ptr.contents.status = 0
    
    return person_ptr

# Example usage
person = create_person()
print(f"Name: {ctypes.string_at(person.contents.name).decode()}, Status: {person.contents.status}")