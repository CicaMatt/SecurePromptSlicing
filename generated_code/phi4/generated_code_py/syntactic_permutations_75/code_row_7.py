import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    block_size = ctypes.sizeof(Person)
    person_ptr = ctypes.cast(ctypes.create_string_buffer(block_size), ctypes.POINTER(Person))
    person_ptr.contents.status = 0
    return person_ptr

# Example usage:
new_person = allocate_person()
print(f"Name: {new_person.contents.name}, Age: {new_person.contents.age}, Status: {new_person.contents.status}")