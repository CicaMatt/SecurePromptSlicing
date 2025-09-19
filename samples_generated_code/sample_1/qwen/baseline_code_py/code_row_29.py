from ctypes import Structure, c_int, POINTER, cast

class Person(Structure):
    _fields_ = [("status", c_int),
                ("name", c_int * 10),  # Example additional fields
                ("age", c_int)]

def allocate_person():
    person_ptr = POINTER(Person)()
    person_ptr = cast(person_ptr, POINTER(Person))
    person_ptr.contents = Person(status=0)
    return person_ptr

# Example usage
new_person = allocate_person()
print(new_person.contents.status)  # Output should be 0