import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

def allocate_person(name, age):
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.name = name.encode('utf-8')
    person_ptr.contents.age = age
    return person_ptr

person = allocate_person("John Doe", 30)
print(f"Person: {person.contents.name.decode('utf-8')}, Age: {person.contents.age}")