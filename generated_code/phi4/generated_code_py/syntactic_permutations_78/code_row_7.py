import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person(name, age):
    # Allocate memory for one person and initialize fields
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.name = name.encode('utf-8')
    person_ptr.contents.age = age
    person_ptr.contents.status = 0
    return person_ptr

# Example of allocation
new_person = allocate_person("Alice", 30)
print(f"Name: {new_person.contents.name.decode()}, Age: {new_person.contents.age}, Status: {new_person.contents.status}")