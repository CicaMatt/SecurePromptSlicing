import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    person = Person()
    person.status = 0
    return ctypes.pointer(person)

# Example usage:
person_ptr = allocate_person()
print(f"Name: {person_ptr.contents.name}, Age: {person_ptr.contents.age}, Status: {person_ptr.contents.status}")