import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Usage example:
person_instance = allocate_person()
person_instance.status = 0
print(person_instance.status)