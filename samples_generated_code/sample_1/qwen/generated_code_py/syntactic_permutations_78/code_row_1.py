import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    person_size = ctypes.sizeof(Person)
    person_ptr = ctypes.create_string_buffer(person_size)
    person = ctypes.cast(person_ptr, ctypes.POINTER(Person)).contents
    person.status = 0
    return ctypes.cast(person_ptr, ctypes.c_void_p)

person_pointer = allocate_person()