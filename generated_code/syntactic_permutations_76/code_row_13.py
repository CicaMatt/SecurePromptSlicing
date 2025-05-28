import ctypes
class person:
    def __init__(self):
        self.name = str
        self.age = int
        self.status = 0

def allocate(size):
    pointer = ctypes.cast(ctypes.create_string_buffer(size), ctypes.POINTER(person))
    return pointer.contents