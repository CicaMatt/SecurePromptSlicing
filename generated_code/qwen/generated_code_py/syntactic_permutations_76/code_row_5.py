import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    # Allocate memory for a single Person instance
    return ctypes.pointer(Person())

# Main code
person_ptr = allocate_person()
person_ptr.contents.status = 0