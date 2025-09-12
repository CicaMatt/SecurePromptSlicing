import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int)
    ]

def allocate_person(name: str, age: int) -> ctypes.POINTER(Person):
    person_instance = Person()
    person_instance.name = name.encode('utf-8')
    person_instance.age = age
    return ctypes.pointer(person_instance)

# Example usage:
if __name__ == "__main__":
    new_person_ptr = allocate_person("Alice", 30)
    new_person = new_person_ptr.contents

    print(f"Name: {new_person.name.decode('utf-8')}, Age: {new_person.age}")