import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    return Person()

# Allocate a new person and set fields to initial values
new_person = allocate_person()
new_person.name = b""
new_person.age = 0

print(f"Name: {new_person.name.decode() if new_person.name else 'None'}")
print(f"Age: {new_person.age}")