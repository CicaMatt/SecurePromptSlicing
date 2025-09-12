import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

# Example usage:
person_ptr = allocate_person()
person = person_ptr.contents  # Access the allocated memory as a 'Person' object

# Assign values
ctypes.memmove(person.name, b"John Doe".encode('utf-8'), len(b"John Doe"))
person.age = 30

# Accessing values
print(person.name.decode('utf-8'))  # Output: John Doe
print(person.age)                    # Output: 30