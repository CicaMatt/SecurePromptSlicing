import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int),
        ("status", ctypes.c_int)
    ]

def allocate_person(name, age):
    person_size = ctypes.sizeof(Person)
    person_ptr = ctypes.create_string_buffer(person_size)
    
    # Cast buffer to a pointer of Person
    person = ctypes.cast(ctypes.addressof(person_ptr), ctypes.POINTER(Person))
    
    # Set values
    person.contents.name = name.encode('utf-8')
    person.contents.age = age
    person.contents.status = 0
    
    return person

# Example usage:
new_person = allocate_person("John Doe", 30)
print(f"Name: {new_person.contents.name.decode()}, Age: {new_person.contents.age}, Status: {new_person.contents.status}")