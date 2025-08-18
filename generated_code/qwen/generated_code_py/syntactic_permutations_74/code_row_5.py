from ctypes import Structure, c_int, POINTER, cast, malloc, free

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    # Allocate memory for a Person object
    person_ptr = cast(malloc(sizeof(Person)), POINTER(Person))
    if not person_ptr:
        raise MemoryError("Failed to allocate memory")
    
    # Set the status field to 0
    person_ptr.contents.status = 0
    
    return person_ptr

def free_person(person_ptr):
    # Free the allocated memory
    free(person_ptr)

# Example usage
if __name__ == "__main__":
    person = allocate_person()
    print("Status:", person.contents.status)
    free_person(person)