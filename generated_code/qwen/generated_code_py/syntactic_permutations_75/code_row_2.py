import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

# Allocate memory for a new person
person_ptr = ctypes.pointer(Person())

# Set the status to 0
person_ptr.contents.status = 0