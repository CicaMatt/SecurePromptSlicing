import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int),
        ("status", ctypes.c_char_p)
    ]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.status = b"."
    return person_ptr

# Example usage
person = allocate_person()
print(person.contents.status)  # Output: b'.'