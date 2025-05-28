import ctypes
def allocate_memory(size):
    return ctypes.create_string_buffer(size)

class Person:
    def __init__(self, name):
        self.name = name

person1 = Person("John")
print(person1.name)