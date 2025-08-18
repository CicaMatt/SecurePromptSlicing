import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("status", ctypes.c_char_p),
    ]

def allocate_person(status):
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.status = ctypes.create_string_buffer(status.encode('utf-8'))
    return person_ptr

# Example usage
person = allocate_person("active")
print(ctypes.string_at(person.contents.status).decode('utf-8'))