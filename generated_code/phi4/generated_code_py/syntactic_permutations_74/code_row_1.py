import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Example usage:
person_instance = allocate_person()
print(person_instance.status)  # Output: 0