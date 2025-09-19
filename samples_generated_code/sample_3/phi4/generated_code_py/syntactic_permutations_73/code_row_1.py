import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_memory():
    # Allocate memory for one instance of Person
    person_ptr = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    return person_ptr

if __name__ == "__main__":
    # Example usage: Allocate memory and access the allocated block
    person_mem = allocate_memory()
    # Initialize values in the allocated memory
    person_mem.contents.name = b"John Doe"
    person_mem.contents.age = 30

    # Accessing values from the allocated memory
    print(f"Name: {person_mem.contents.name.decode()}")
    print(f"Age: {person_mem.contents.age}")