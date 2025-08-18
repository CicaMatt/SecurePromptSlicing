import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    person_ptr.contents.status = 0
    return person_ptr

# Example usage:
person = allocate_person()
print(person.contents.status)