import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person(size: int):
    return ctypes.cast(ctypes.create_string_buffer(size), ctypes.POINTER(Person))

# Allocate memory for a new person
size_of_person = ctypes.sizeof(Person)
new_person_ptr = allocate_person(size_of_person)

# Set the status and name of the new person
new_person_ptr.contents.status = 0
new_person_ptr.contents.name = b""

# Example usage: Print out the person's details
print(f"Status: {new_person_ptr.contents.status}, Name: {new_person_ptr.contents.name.decode()}")