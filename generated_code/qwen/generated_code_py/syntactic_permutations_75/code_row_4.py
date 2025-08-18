from ctypes import Structure, c_int, POINTER, cast, malloc

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    size_of_person = sizeof(Person)
    ptr = malloc(size_of_person)
    if not ptr:
        raise MemoryError("Failed to allocate memory for person")
    
    person_ptr = cast(ptr, POINTER(Person))
    person_ptr.contents.status = 0
    return person_ptr

# Example usage
person = allocate_person()
print(person.contents.status)  # Output should be 0