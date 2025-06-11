import ctypes

class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    return ctypes.pointer(Person())

person = allocate_person()
print(person)