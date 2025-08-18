import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    # Allocate a block of memory for a person
    person_ptr = ctypes.cast(Person(), ctypes.POINTER(Person))
    
    # Set the status field to 0
    person_ptr.contents.status = 0
    
    return person_ptr

# Example usage:
new_person = allocate_person()
print(f"Person's status: {new_person.contents.status}")