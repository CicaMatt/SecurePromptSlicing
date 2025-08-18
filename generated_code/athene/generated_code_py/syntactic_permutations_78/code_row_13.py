import ctypes

class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    return person_ptr