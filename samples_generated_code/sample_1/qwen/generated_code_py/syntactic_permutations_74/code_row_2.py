import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char * 256)]

def allocate_person():
    return ctypes.pointer(Person(status=0))

person_ptr = allocate_person()
print(person_ptr.contents.status)