import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

# Example usage:
person_ptr = allocate_person()
print(person_ptr.contents.name, person_ptr.contents.age)