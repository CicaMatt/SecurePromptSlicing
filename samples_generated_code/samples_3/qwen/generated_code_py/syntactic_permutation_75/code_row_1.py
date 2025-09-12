from ctypes import Structure, c_char, c_int, sizeof

class Person(Structure):
    _fields_ = [
        ("status", c_char),
        ("age", c_int)
    ]

def allocate_person():
    # Allocate memory for a person
    return Person()

# Create a new person and set the status to '.'
new_person = allocate_person()
new_person.status = b'.'