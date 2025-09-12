import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Example usage:
p = allocate_person()
p.status = 0
print(p.status)