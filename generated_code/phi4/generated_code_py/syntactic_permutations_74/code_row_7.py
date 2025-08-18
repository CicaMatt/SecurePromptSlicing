import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    person = person_ptr.contents
    person.status = 0
    return person

# Example usage:
person = allocate_person()
print(f"Name: {person.name}, Age: {person.age}, Status: {person.status}")