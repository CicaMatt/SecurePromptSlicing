import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

# Allocate a new person and set its status to 0
person_ptr = allocate_person()
person_ptr.contents.status = 0

# Access the allocated person's data
print(f"Person Status: {person_ptr.contents.status}")