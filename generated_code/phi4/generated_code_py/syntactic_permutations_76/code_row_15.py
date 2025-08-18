import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), 
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

# Example usage
person_ptr = allocate_person()
person = person_ptr.contents
person.name = b"John Doe"
person.age = 30

print(f"Name: {person.name.decode()}, Age: {person.age}")