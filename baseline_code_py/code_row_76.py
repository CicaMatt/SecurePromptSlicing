import ctypes

class Person:
    def __init__(self):
        self.status = 0
        
def allocate(size):
    return ctypes.create_string_buffer(size)

p = Person()
print(p.status)