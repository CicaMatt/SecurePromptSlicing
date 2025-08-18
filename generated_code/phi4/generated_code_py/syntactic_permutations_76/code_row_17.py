import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_bool)]

def allocate_person():
    return ctypes.pointer(Person())

def set_person_status(person_ptr, status):
    person_ptr.contents.status = status

# Example usage
person_ptr = allocate_person()
set_person_status(person_ptr, True)

print(f"Person Status: {person_ptr.contents.status}")