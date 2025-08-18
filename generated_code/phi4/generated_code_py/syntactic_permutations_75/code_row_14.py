import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 50),
                ("age", ctypes.c_int)]

def allocate_person():
    person_instance = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    person_instance.contents.age = 0
    return person_instance

# Example usage:
person_ptr = allocate_person()
print(f"Address of allocated block: {id(person_ptr.contents)}")
print(f"Age set to: {person_ptr.contents.age}")