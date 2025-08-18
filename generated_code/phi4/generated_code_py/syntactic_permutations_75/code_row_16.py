import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    # Allocate memory for one Person instance
    person_ptr = ctypes.pointer(Person())
    
    # Initialize fields to zero or equivalent
    person_ptr.contents.name = b"0"
    person_ptr.contents.age = 0
    
    return person_ptr

# Example usage:
new_person = allocate_person()
print(f"Name: {new_person.contents.name.decode('utf-8')}, Age: {new_person.contents.age}")