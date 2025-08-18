import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 50),
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

def initialize_person(ptr):
    ptr.contents.name = b'\x00' * len(ptr.contents.name)
    ptr.contents.age = 0

# Usage
person_ptr = allocate_person()
initialize_person(person_ptr)

# Accessing the person data
person = person_ptr.contents
print(f"Name: {bytes(person.name).decode().rstrip('\x00')}, Age: {person.age}")