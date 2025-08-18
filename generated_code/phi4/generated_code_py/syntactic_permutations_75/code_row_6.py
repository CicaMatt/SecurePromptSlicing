import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Example usage:
new_person = allocate_person()
new_person.status = 0
print(f"Name: {new_person.name}, Age: {new_person.age}, Status: {new_person.status}")