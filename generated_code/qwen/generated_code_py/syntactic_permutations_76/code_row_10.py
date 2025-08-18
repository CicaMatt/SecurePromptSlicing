from ctypes import Structure, c_int, cast, POINTER

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    return cast(Person(), POINTER(Person))

person_ptr = allocate_person()
person_ptr.contents.status = 0