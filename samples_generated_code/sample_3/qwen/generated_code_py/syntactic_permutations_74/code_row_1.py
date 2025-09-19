import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    person_size = ctypes.sizeof(Person)
    ptr = ctypes.create_string_buffer(person_size)
    person_ptr = ctypes.cast(ptr, ctypes.POINTER(Person))
    person_ptr.contents.status = 0
    return person_ptr

person = allocate_person()
print(f"Person status: {person.contents.status}")