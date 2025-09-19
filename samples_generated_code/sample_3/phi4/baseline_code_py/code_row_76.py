import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int), ("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Allocate a new person and set the status to 0
person_instance = allocate_person()
person_instance.status = 0

# Example usage:
print(f"Name: {person_instance.name}, Age: {person_instance.age}, Status: {person_instance.status}")