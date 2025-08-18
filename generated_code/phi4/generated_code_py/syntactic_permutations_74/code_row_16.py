import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100),
                ("age", ctypes.c_int)]

def allocate_person():
    return Person()

# Example usage:
new_person = allocate_person()
new_person.age = 0
for i in range(len(new_person.name)):
    new_person.name[i] = b'\x00'  # Set the name field to zero

print(f"Age: {new_person.age}")
print(f"Name: {new_person.name.decode('utf-8').rstrip('\x00')}")