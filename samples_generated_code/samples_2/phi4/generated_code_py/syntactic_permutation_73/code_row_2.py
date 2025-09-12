import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int)
    ]

def allocate_person():
    return ctypes.cast(Person(), ctypes.POINTER(Person))

# Example usage:
person_ptr = allocate_person()
person_instance = person_ptr.contents
person_instance.name = b"John Doe"
person_instance.age = 30

print(person_instance.name.decode('utf-8'))  # Output: John Doe
print(person_instance.age)                    # Output: 30