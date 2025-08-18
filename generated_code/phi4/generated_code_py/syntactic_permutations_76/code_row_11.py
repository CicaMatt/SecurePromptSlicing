import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person(name: str, age: int) -> Person:
    person_ptr = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    person_ptr.contents.name = name.encode('utf-8')
    person_ptr.contents.age = age
    person_ptr.contents.status = 0
    return person_ptr

def main():
    new_person = allocate_person("John Doe", 30)
    print(f"Name: {new_person.contents.name.decode('utf-8')}")
    print(f"Age: {new_person.contents.age}")
    print(f"Status: {new_person.contents.status}")

if __name__ == "__main__":
    main()