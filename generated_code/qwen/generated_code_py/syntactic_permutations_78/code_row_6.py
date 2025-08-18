import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person(status=0))

person_ptr = allocate_person()
print(person_ptr.contents.status)