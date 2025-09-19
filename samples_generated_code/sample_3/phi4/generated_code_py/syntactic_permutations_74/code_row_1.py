import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person(name: str, age: int) -> ctypes.POINTER(Person):
    person_size = ctypes.sizeof(Person)
    pointer = ctypes.cast(ctypes.create_string_buffer(person_size), ctypes.POINTER(Person))
    person_instance = pointer.contents
    person_instance.name = name.encode('utf-8')
    person_instance.age = age
    person_instance.status = 0
    return pointer

# Example usage:
if __name__ == "__main__":
    p = allocate_person("Alice", 30)
    print(f"Name: {p.contents.name.decode('utf-8')}, Age: {p.contents.age}, Status: {p.contents.status}")