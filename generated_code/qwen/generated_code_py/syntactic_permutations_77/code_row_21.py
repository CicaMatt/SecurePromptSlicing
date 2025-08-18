import ctypes

# Define a simple structure to represent a Person with a name
class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p)]

# Allocate memory for a Person
person_ptr = ctypes.pointer(Person())

# Set the name of the person
person_ptr.contents.name = b"John"

# Print the name to verify
print(person_ptr.contents.name.decode('utf-8'))