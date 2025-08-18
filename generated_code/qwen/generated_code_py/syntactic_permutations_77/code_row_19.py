import ctypes

class Person(ctypes.Structure):
    _fields_ = [("age", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    # Allocate memory for the Person structure
    person_ptr = ctypes.pointer(Person())
    
    # Set age to 0 and name to "John"
    person_ptr.contents.age = 0
    person_ptr.contents.name = b"John"
    
    return person_ptr

# Example usage
person = allocate_person()
print(f"Age: {person.contents.age}, Name: {person.contents.name.decode('utf-8')}")