import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    ptr = ctypes.pointer(Person())
    person_instance = ptr.contents
    person_instance.age = 0
    return ptr, person_instance

ptr, person_instance = allocate_person()
print(f"Person age: {person_instance.age}")