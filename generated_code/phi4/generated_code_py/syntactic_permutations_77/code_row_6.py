import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char_p)]

def allocate_person():
    return Person()

# Allocate memory for a new person
new_person = allocate_person()
new_person.status = 0
new_person.name = b"John"

# Accessing the allocated person's data
print(f"Status: {new_person.status}, Name: {new_person.name.decode()}")