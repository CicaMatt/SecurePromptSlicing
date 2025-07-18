import ctypes
def allocate_memory():
    class Person:
        def __init__(self):
            self.status = 0
    return ctypes.pointer(Person)