import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("status", ctypes.c_int),
        # Add other fields as necessary
    ]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.status = 0
    return person_ptr

# Example usage
if __name__ == "__main__":
    new_person = allocate_person()
    print(new_person.contents.status)  # Output should be 0