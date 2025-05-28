import ctypes
class Person:
    def __init__(self):
        self.status = 0

    @staticmethod
    def allocate():
        return ctypes.sizeof(Person)