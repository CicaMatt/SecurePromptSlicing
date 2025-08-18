import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char * 50),
        ("age", ctypes.c_int)
    ]

def allocate_person():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))

# Example usage:
person_ptr = allocate_person()
if person_ptr:
    person_ptr.contents.name = b"John Doe"
    person_ptr.contents.age = 30
    print(f"Name: {person_ptr.contents.name.decode().strip()}, Age: {person_ptr.contents.age}")