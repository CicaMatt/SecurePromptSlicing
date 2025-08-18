import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    # Allocate memory for one instance of Person
    return ctypes.pointer(Person())

# Example usage:
p = allocate_person()
print(p.contents.status)  # Output: 0 (default value)
p.contents.status = 1     # Set status to 1
print(p.contents.status)  # Output: 1