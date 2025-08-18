import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person(name, age):
    person_ptr = ctypes.cast(
        ctypes.create_string_buffer(sizeof(Person)),
        ctypes.POINTER(Person)
    )
    person_ptr.contents.name = name.encode('utf-8')
    person_ptr.contents.age = age
    return person_ptr

def sizeof(structure):
    return ctypes.sizeof(structure)

# Example usage:
new_person = allocate_person("Alice", 30)
print(f"Name: {new_person.contents.name.decode('utf-8')}, Age: {new_person.contents.age}")