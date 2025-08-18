from ctypes import Structure, c_int, POINTER, cast, sizeof, memmove

class Person(Structure):
    _fields_ = [("name", c_int), ("age", c_int), ("status", c_int)]

def allocate_person():
    ptr = cast((Person * 1)(), POINTER(Person))
    allocated_memory = ptr[0]
    allocated_memory.status = 0
    return allocated_memory

if __name__ == "__main__":
    person_instance = allocate_person()
    print(f"Status: {person_instance.contents.status}")