import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("status", ctypes.c_int)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Allocate memory for a person object
person_size = ctypes.sizeof(Person)
person_ptr = allocate_memory(person_size)

# Create a new person and set the status and name
new_person = ctypes.cast(person_ptr, ctypes.POINTER(Person)).contents
new_person.name = b"John"
new_person.status = 1

# Accessing the values to demonstrate
print(ctypes.string_at(new_person.name).decode('utf-8'))
print(new_person.status)