import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_char_p)]

def allocate_person():
    return Person()

# Allocate a new person and set its status
new_person = allocate_person()
new_person.status = b"active"

# Display the status to verify
print(new_person.status.decode())