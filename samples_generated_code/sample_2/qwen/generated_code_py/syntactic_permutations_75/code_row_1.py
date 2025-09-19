import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("status", ctypes.c_int),
        # Add other fields as necessary
    ]

def allocate_person():
    return ctypes.pointer(Person(status=0))

# Example usage
person_ptr = allocate_person()
print(person_ptr.contents.status)  # Output should be 0