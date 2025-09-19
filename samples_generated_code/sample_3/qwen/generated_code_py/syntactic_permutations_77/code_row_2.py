import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("status", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

person_size = ctypes.sizeof(Person)
person_ptr = allocate_memory(person_size)

new_person = ctypes.cast(person_ptr, ctypes.POINTER(Person))
new_person.contents.name = b"John"
new_person.contents.status = b"Active"

print(f"Name: {new_person.contents.name.decode()}, Status: {new_person.contents.status.decode()}")