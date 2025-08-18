from ctypes import Structure, c_int, POINTER, cast, addressof, memmove

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    # Allocate memory for one instance of Person
    person_pointer = cast(addressof(Person()), POINTER(Person))
    return person_pointer

# Create a new person and set its status to 0
new_person = allocate_person()
new_person.contents.status = 0

# Example usage: Print the status of the allocated person
print(new_person.contents.status)