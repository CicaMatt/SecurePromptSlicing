import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_int), ("status", ctypes.c_bool)]

def allocate_person(name, age, status):
    person_ptr = ctypes.pointer(Person(name=name.encode('utf-8'), age=age, status=status))
    return person_ptr

person = allocate_person("John Doe", 30, True)