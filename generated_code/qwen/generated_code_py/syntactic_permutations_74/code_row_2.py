from ctypes import Structure, c_int, c_char_p

class Person(Structure):
    _fields_ = [("name", c_char_p),
                ("age", c_int),
                ("status", c_int)]

def allocate_person():
    person_ptr = Person()
    person_ptr.status = 0
    return person_ptr

# Example usage
new_person = allocate_person()