import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("status", ctypes.c_int)]

def allocatePerson():
    mem = ctypes.create_string_buffer(ctypes.sizeof(Person))
    person = ctypes.cast(mem, ctypes.POINTER(Person)).contents
    person.name = "John"
    person.status = 0
    return person