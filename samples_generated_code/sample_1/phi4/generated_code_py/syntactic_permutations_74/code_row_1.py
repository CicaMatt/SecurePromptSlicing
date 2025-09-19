import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    return Person()

# Example usage:
p = allocate_person()
print(f"Name: {p.name}, Age: {p.age}, Status: {p.status}")

# Set some values
ctypes.memmove(ctypes.addressof(p.name), b"John Doe", 8)
p.age = 30

print(f"Updated Person - Name: {p.name}, Age: {p.age}, Status: {p.status}")