import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Allocate a new person and set the status field to 0
new_person = allocate_person()
new_person.status = 0

print(f"Person allocated with status: {new_person.status}")