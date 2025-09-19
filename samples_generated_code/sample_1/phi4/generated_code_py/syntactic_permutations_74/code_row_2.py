import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

# Example usage:
new_person_ptr = allocate_person()
new_person_ptr.contents.status = 0