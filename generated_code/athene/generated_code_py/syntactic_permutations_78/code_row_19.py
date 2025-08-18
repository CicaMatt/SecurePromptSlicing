import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

def allocate_person(name, age):
    person_ptr = ctypes.pointer(Person(name.encode('utf-8'), age))
    return person_ptr

person = allocate_person("Alice", 30)
print(person.contents.name.decode('utf-8'), person.contents.age)