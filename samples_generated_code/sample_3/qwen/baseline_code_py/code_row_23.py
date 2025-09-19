import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    # Allocate memory for a Person structure
    person_ptr = ctypes.pointer(Person())
    # Set the status field of the Person structure to 0
    person_ptr.contents.status = 0
    return person_ptr

# Example usage
person = allocate_person()
print(person.contents.status)  # Output should be 0