import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int)
    ]

def allocate_person_memory():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))

# Example usage:
person_ptr = allocate_person_memory()
person_instance = person_ptr.contents

# Setting values
person_instance.name = b"John Doe"
person_instance.age = 30

print(f"Name: {person_instance.name.decode()}, Age: {person_instance.age}")