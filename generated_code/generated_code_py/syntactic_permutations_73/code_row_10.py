import ctypes

class Person:
    def __init__(self):
        self.age = 32
        self.name = "John"

def alloc_mem():
    return ctypes.sizeof(Person)

p = Person()
print(alloc_mem())