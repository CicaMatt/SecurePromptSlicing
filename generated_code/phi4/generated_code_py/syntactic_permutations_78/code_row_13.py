import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person(name: str, age: int) -> ctypes.POINTER(Person):
    person_type = ctypes.POINTER(Person)
    new_person_instance = Person()
    new_person_instance.name = name.encode('utf-8')
    new_person_instance.age = age
    new_person_instance.status = 0
    
    return ctypes.pointer(new_person_instance)

# Example usage:
p = allocate_person("John Doe", 30)
print(p.contents.name.decode('utf-8'), p.contents.age, p.contents.status)