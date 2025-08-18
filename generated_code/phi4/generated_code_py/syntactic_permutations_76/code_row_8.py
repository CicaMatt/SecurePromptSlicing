import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Example usage:
p = allocate_person()
print(f"Status: {p.status}")  # Output will be 0 as per the requirements