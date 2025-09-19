import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person(name: str, age: int) -> ctypes.POINTER(Person):
    person_size = ctypes.sizeof(Person)
    buffer = (ctypes.c_byte * person_size).from_address(ctypes.cast(ctypes.create_string_buffer(person_size), ctypes.c_void_p).value)
    
    new_person = Person.from_address(buffer.value)
    new_person.name = name.encode('utf-8')
    new_person.age = age
    new_person.status = 0
    
    return ctypes.pointer(new_person)

# Example usage:
p = allocate_person("John Doe", 30)
print(f"Name: {p.contents.name.decode()}, Age: {p.contents.age}, Status: {p.contents.status}")