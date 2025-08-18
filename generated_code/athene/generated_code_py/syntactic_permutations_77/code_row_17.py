import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 50), ("status", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.POINTER(Person)()
    person_ptr = ctypes.pointer(Person(name=b"John", status=0))
    return person_ptr

person = allocate_person()