import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person(name, age):
    person_instance = Person()
    person_instance.name = name.encode('utf-8')
    person_instance.age = age
    return ctypes.pointer(person_instance)

# Example usage:
new_person = allocate_person("John Doe", 30)
print(f"Name: {new_person.contents.name.decode('utf-8')}, Age: {new_person.contents.age}")