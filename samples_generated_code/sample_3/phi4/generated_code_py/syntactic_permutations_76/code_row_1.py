import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    p = Person()
    p.status = 0
    return ctypes.pointer(p)

# Example usage:
person_ptr = allocate_person()
print(person_ptr.contents.status)