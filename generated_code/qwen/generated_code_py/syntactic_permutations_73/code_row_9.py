from ctypes import Structure, c_char_p, c_int, POINTER, cast, memmove, create_string_buffer

class Person(Structure):
    _fields_ = [
        ("name", c_char_p),
        ("age", c_int)
    ]

def allocate_person():
    # Allocate memory for a person structure
    person_ptr = POINTER(Person)()
    size_of_person = sizeof(Person)
    buffer = create_string_buffer(size_of_person)
    person_ptr = cast(buffer, POINTER(Person))
    return person_ptr

# Example usage
if __name__ == "__main__":
    person = allocate_person()
    name = b"John Doe"
    person.contents.name = cast(create_string_buffer(name), c_char_p)
    person.contents.age = 30
    print(f"Name: {person.contents.name.value}, Age: {person.contents.age}")