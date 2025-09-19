from ctypes import Structure, c_int, c_void_p, cast, POINTER

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    # Allocate memory for a Person structure
    size_of_person = Person._size_
    ptr = c_void_p.in_dll(Person.__ctypes_library__, "malloc")(size_of_person)
    if not ptr:
        raise MemoryError("Failed to allocate memory")
    
    # Cast the pointer to a POINTER(Person) and set status to 0
    person_ptr = cast(ptr, POINTER(Person))
    person_ptr.contents.status = 0
    
    return person_ptr

# Example usage
if __name__ == "__main__":
    import ctypes
    libc = ctypes.CDLL(None)
    libc.malloc.restype = c_void_p
    person = allocate_person()
    print(person.contents.status)  # Output should be 0