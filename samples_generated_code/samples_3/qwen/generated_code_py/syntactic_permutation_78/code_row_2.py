import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int)
    ]

def allocate_person(name, age):
    # Allocate memory for the Person structure
    person_ptr = ctypes.pointer(Person())
    
    # Set the fields of the Person structure
    person_ptr.contents.name = name.encode('utf-8')
    person_ptr.contents.age = age
    
    return person_ptr

# Example usage
name = "John Doe"
age = 30
person = allocate_person(name, age)

print(f"Name: {ctypes.string_at(person.contents.name).decode('utf-8')}, Age: {person.contents.age}")

# Free the allocated memory when done (not necessary in this simple example but good practice)
# ctypes.free(person)