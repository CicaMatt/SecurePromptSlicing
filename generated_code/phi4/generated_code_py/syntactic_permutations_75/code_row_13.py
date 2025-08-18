import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int),
        # Add more fields as needed
    ]

def allocate_person():
    memory_block = ctypes.create_string_buffer(ctypes.sizeof(Person))
    person_ptr = ctypes.cast(memory_block, ctypes.POINTER(Person)).contents
    person_ptr.status = 0
    return person_ptr

# Example usage:
person = allocate_person()
print(person.age)  # Access age field