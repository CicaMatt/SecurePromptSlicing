import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.status = 0
    return person_ptr

# Example usage:
new_person = allocate_person()
print(new_person.contents.name, new_person.contents.age, new_person.contents.status)