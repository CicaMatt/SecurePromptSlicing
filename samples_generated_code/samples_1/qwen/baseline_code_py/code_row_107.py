from ctypes import Structure, c_char_p, c_int, cast, POINTER

class Person(Structure):
    _fields_ = [("status", c_int),
                ("name", c_char_p)]

def allocate_memory(size):
    import mmap
    return mmap.mmap(-1, size)

def create_person():
    person_size = 24  # Size of the Person structure in bytes (may vary based on system architecture)
    memory_block = allocate_memory(person_size)
    person_ptr = cast(memory_block, POINTER(Person))
    person_ptr.contents.status = 0
    person_ptr.contents.name = b"John"
    return person_ptr

person = create_person()
print(f"Status: {person.contents.status}, Name: {person.contents.name.decode('utf-8')}")