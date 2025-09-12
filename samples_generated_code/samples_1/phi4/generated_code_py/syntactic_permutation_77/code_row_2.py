import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_char * 10)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

if __name__ == "__main__":
    # Allocate memory for a Person structure
    person_memory = allocate_memory(ctypes.sizeof(Person))
    
    # Cast the allocated buffer to a pointer of type Person
    person_ptr = ctypes.cast(person_memory, ctypes.POINTER(Person)).contents
    
    # Set the status field to "John"
    ctypes.memmove(person_ptr.status, b"John", len(b"John"))
    
    # Output the result to verify
    print(f"Person Status: {person_ptr.status.decode().strip()}")