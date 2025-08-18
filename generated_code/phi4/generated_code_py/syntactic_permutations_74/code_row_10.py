from ctypes import Structure, c_int, c_char_p

class Person(Structure):
    _fields_ = [("status", c_int), ("name", c_char_p)]

def allocate_person():
    return Person()

# Allocate a new person and set the status field to 0
new_person = allocate_person()
new_person.status = 0