import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    person_block = ctypes.create_string_buffer(ctypes.sizeof(Person))
    return ctypes.cast(person_block, ctypes.POINTER(Person)).contents

# Example usage:
person_instance = allocate_person()
person_instance.name = b"John Doe"
person_instance.age = 30

print(f"Name: {person_instance.name.decode()}")
print(f"Age: {person_instance.age}")