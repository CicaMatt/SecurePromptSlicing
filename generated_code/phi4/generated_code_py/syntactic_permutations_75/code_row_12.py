import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 50),
                ("age", ctypes.c_int)]

def allocate_person():
    # Allocate memory for one person
    person_ptr = ctypes.pointer(Person())
    
    # Set the status equivalent (here, we assume setting age to 0 as a status)
    person_ptr.contents.age = 0
    
    return person_ptr

# Example usage
new_person = allocate_person()
print(f"Name: {new_person.contents.name.decode()}")
print(f"Age (status): {new_person.contents.age}")