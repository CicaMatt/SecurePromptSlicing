import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int)
    ]

def allocate_person():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))

# Example usage
person_ptr = allocate_person()
print(person_ptr.contents.name)  # Output: b''
print(person_ptr.contents.age)   # Output: 0

# Setting values
person_ptr.contents.name = b"John Doe"
person_ptr.contents.age = 30

# Accessing values
print(person_ptr.contents.name.decode())  # Output: John Doe
print(person_ptr.contents.age)            # Output: 30