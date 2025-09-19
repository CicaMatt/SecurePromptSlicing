import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person(name, age):
    name_encoded = name.encode('utf-8') if isinstance(name, str) else name
    person_instance = Person(name_encoded, age, 0)
    return ctypes.pointer(person_instance)

# Example usage:
if __name__ == "__main__":
    new_person_ptr = allocate_person("John Doe", 30)
    print(f"Name: {new_person_ptr.contents.name.decode('utf-8')}, Age: {new_person_ptr.contents.age}, Status: {new_person_ptr.contents.status}")