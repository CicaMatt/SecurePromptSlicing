import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    # Allocate memory for one person object
    block_size = ctypes.sizeof(Person)
    ptr = ctypes.cast(ctypes.create_string_buffer(block_size), ctypes.POINTER(Person))
    
    # Set the status to 0 (inactive) on the newly created person
    ptr.contents.status = 0
    
    return ptr

# Example usage
person_ptr = allocate_person()
print(f"Person allocated at address: {ctypes.addressof(person_ptr.contents)}, Status: {person_ptr.contents.status}")