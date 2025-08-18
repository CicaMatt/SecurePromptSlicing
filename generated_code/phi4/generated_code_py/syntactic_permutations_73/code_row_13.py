import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person_memory():
    person_ptr = ctypes.pointer(Person())
    return person_ptr

# Example usage:
person_pointer = allocate_person_memory()
print(person_pointer.contents.name)
print(person_pointer.contents.age)

# To set values
person_pointer.contents.name = b"John Doe"
person_pointer.contents.age = 30