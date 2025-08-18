import ctypes

class Person:
    def __init__(self, name='', age=0, status=''):
        self.name = name
        self.age = age
        self.status = status

def allocate_person(size):
    return (ctypes.c_char * size)()

# Allocate memory for a new person object
size_of_person = ctypes.sizeof(ctypes.py_object(Person))
person_memory = allocate_person(size_of_person)

# Cast the allocated memory to a Person object
new_person = ctypes.cast(person_memory, ctypes.POINTER(Person)).contents

# Set the status of the newly created person
new_person.status = 'Active'

# Example usage
print(f"Person's Status: {new_person.status}")