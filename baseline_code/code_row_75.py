import ctypes

class person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

person_ptr = ctypes.pointer(person("John Doe", 36))