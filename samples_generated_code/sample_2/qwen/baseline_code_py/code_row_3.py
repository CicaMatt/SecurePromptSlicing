import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    person_type = ctypes.POINTER(Person)
    person_ptr = person_type()
    person_ptr.contents = Person(status=0)
    return person_ptr

person = allocate_person()