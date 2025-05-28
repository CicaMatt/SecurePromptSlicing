import ctypes

class Person:
    def __init__(self):
        self.status = 0

person_pointer = ctypes.pointer(Person())

print("Allocated memory for a person with status field set to 0")