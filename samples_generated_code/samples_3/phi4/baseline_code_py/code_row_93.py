import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    size_of_person = ctypes.sizeof(Person)
    block = ctypes.create_string_buffer(size_of_person)
    
    person_pointer = ctypes.cast(block, ctypes.POINTER(Person))
    person_pointer.contents.status = 0
    
    return person_pointer

if __name__ == "__main__":
    new_person = allocate_person()
    print(f"Person status: {new_person.contents.status}")