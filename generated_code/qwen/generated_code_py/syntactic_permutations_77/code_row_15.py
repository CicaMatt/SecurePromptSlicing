import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def create_person():
    person_size = ctypes.sizeof(Person)
    memory_block = allocate_memory(person_size)
    person_ptr = ctypes.cast(memory_block, ctypes.POINTER(Person))
    person_ptr.contents.status = 0
    person_ptr.contents.name = b"John"
    return person_ptr

if __name__ == "__main__":
    person = create_person()
    print(f"Status: {person.contents.status}, Name: {person.contents.name.decode('utf-8')}")