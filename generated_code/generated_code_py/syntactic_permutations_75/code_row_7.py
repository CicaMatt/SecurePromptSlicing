import ctypes
class Person:
    def __init__(self):
        self.status = 0
def allocate_memory():
    return ctypes.sizeof(Person)
def new_person():
    return Person()