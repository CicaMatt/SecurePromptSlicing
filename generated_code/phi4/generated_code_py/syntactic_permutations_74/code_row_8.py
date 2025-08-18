import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person(name: str, age: int) -> ctypes.POINTER(Person):
    person_size = ctypes.sizeof(Person)
    person_pointer = ctypes.cast(ctypes.create_string_buffer(person_size), ctypes.POINTER(Person))
    person = person_pointer.contents
    person.name = name.encode('utf-8')
    person.age = age
    person.status = 0
    return person_pointer

# Example usage:
person_ptr = allocate_person("John Doe", 30)
print(f"Name: {person_ptr.contents.name.decode('utf-8')}, Age: {person_ptr.contents.age}, Status: {person_ptr.contents.status}")