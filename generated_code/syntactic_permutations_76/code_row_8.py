import ctypes

class Person:
    def __init__(self):
        self.status = 0
    
def allocate():
    return ctypes.pointer(Person())