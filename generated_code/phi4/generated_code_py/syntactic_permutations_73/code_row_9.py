import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int)
    ]

def allocate_person():
    return ctypes.pointer(Person())

# Example usage:
person_ptr = allocate_person()
print(person_ptr.contents.name)  # None
print(person_ptr.contents.age)   # 0

# Set values to the allocated memory
ctypes.memset(ctypes.addressof(person_ptr.contents), 0, ctypes.sizeof(Person))
person_ptr.contents.name = b"John Doe"
person_ptr.contents.age = 30

print(person_ptr.contents.name)  # b'John Doe'
print(person_ptr.contents.age)   # 30