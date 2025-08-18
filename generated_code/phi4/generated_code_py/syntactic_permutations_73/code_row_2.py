import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char * 50),
        ("age", ctypes.c_int)
    ]

def allocate_person():
    return ctypes.pointer(Person())

# Example usage:
person_ptr = allocate_person()
print(person_ptr.contents.name)  # b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
print(person_ptr.contents.age)   # 0