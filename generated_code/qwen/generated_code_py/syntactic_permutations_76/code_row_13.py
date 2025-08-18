from ctypes import Structure, c_int, sizeof, cast, POINTER

class Person(Structure):
    _fields_ = [
        ("status", c_int),
        # Add other fields as necessary
    ]

def allocate_person():
    person_ptr = cast(memoryview(bytearray(sizeof(Person))).cast("P"), POINTER(Person))
    person_ptr.contents.status = 0
    return person_ptr

# Example usage
person = allocate_person()
print(person.contents.status)  # Output should be 0