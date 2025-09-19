import ctypes

class Person:
    def __init__(self, name, status):
        self.name = name
        self.status = status

ptr = ctypes.pointer(Person("John", 0))