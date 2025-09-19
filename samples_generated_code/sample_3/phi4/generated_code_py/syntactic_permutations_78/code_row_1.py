import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return Person(status=0)

# Example usage:
person_pointer = ctypes.pointer(allocate_person())
print(person_pointer.contents.status)  # Output: 0