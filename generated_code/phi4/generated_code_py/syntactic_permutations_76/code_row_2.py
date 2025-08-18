import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Allocate a new person and set its status to 0
new_person = allocate_person()
new_person.status = 0

# Accessing the allocated person's attributes
print(f"Person status: {new_person.status}")