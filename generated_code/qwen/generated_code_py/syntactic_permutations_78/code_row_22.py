import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_char_p)]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.status = b"active"
    return person_ptr

person = allocate_person()
print(person.contents.status)