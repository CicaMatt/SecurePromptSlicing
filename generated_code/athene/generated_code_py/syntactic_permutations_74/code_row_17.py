import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int), ("status", ctypes.c_int)]

def allocate_person(name, age, status):
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.name = name.encode('utf-8')
    person_ptr.contents.age = age
    person_ptr.contents.status = status
    return person_ptr

person = allocate_person("John Doe", 30, 1)