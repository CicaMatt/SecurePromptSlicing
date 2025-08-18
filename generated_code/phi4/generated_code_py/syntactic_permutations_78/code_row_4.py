import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    # Create a new instance of Person
    person_ptr = ctypes.pointer(Person())
    
    # Set the status to 0
    person_ptr.contents.status = 0
    
    return person_ptr

# Example usage:
person_block = allocate_person()
print(f"Person name: {person_block.contents.name}")
print(f"Person age: {person_block.contents.age}")
print(f"Person status: {person_block.contents.status}")