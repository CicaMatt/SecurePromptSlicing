from ctypes import Structure, c_char_p, c_int, sizeof

class Person(Structure):
    _fields_ = [("name", c_char_p),
                ("age", c_int)]

def allocate_person():
    return Person()

# Example usage
person = allocate_person()
person.name = b"John Doe"
person.age = 30

print(f"Name: {person.name.decode()}, Age: {person.age}")