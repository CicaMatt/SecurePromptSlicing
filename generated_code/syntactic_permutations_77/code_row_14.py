import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ('status', ctypes.c_int),
        ('name', ctypes.c_char_p)
    ]

def create_person():
    person = Person()
    person.status = 0
    person.name = "John"
    return person