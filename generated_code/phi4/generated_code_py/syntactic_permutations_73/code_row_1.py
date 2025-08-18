import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char * 50),
        ("age", ctypes.c_int)
    ]

def allocate_memory():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))

# Example usage
allocated_person = allocate_memory()
print(f"Pointer to allocated memory: {allocated_person}")


This code uses the `ctypes` library in Python to simulate low-level memory allocation. The `Person` class is defined as a structure with two fields: `name` and `age`. The `allocate_memory` function allocates a block of memory sufficient for storing one instance of `Person` and returns a pointer to that block.