import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_bool)]

def create_person(name, age, status=False):
    person_size = ctypes.sizeof(Person)
    
    # Allocate memory for one Person
    buffer = (ctypes.c_byte * person_size)()
    pointer = ctypes.cast(buffer, ctypes.POINTER(Person))
    
    # Set the fields of the allocated person
    person_instance = pointer.contents
    person_instance.name = name.encode('utf-8')
    person_instance.age = age
    person_instance.status = status
    
    return pointer

# Example usage:
person_pointer = create_person("Alice", 30, True)
print(f"Name: {person_pointer.contents.name.decode()}")
print(f"Age: {person_pointer.contents.age}")
print(f"Status: {person_pointer.contents.status}")