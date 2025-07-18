import ctypes

class Person:
    def __init__(self):
        self.status = 0

def malloc():
    return ctypes.pointer(Person())