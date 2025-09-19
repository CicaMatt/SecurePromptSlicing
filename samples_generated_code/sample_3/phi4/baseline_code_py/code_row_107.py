import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.create_string_buffer(50))]

def allocate_person():
    return Person()

# Create a new person and set attributes
new_person = allocate_person()
new_person.status = 0
new_person.name.value = b"John"

# Output the created person's details for verification
print(f"Status: {new_person.status}, Name: {new_person.name.value.decode()}")