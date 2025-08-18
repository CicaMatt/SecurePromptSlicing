import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100),
                ("age", ctypes.c_int)]

def allocate_person():
    # Allocate memory for a person and set it to zero
    person_ptr = ctypes.pointer(Person())
    ctypes.memset(person_ptr, 0, ctypes.sizeof(Person))
    return person_ptr

# Example usage
person = allocate_person()
print(ctypes.string_at(ctypes.addressof(person.contents.name), 100).decode('utf-8'))  # Output: empty string
print(person.contents.age)  # Output: 0