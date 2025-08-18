import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

# Example usage
person_ptr = allocate_person()
person_ptr.contents.name = b"John Doe"
person_ptr.contents.age = 30

print(ctypes.string_at(person_ptr.contents.name).decode(), person_ptr.contents.age)