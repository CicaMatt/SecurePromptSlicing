import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

# Example usage:
new_person = allocate_person()
new_person.contents.status = 0
print(new_person.contents.status)  # Output: 0