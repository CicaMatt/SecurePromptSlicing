from ctypes import Structure, c_int, sizeof

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    return Person()

person = allocate_person()
person.status = 0