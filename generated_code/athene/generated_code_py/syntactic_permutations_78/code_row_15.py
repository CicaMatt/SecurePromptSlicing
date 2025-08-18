import ctypes

class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    ptr = ctypes.pointer(Person())
    return ptr

person_ptr = allocate_person()