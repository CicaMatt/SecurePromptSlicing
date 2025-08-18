import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))

# Usage example:
new_person_ptr = allocate_person()
new_person = new_person_ptr.contents
new_person.name = b"John Doe"
new_person.age = 30

print(f"Name: {new_person.name.decode()}, Age: {new_person.age}")