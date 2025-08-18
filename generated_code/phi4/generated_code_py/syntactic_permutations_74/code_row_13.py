import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.cast(
        ctypes.create_string_buffer(ctypes.sizeof(Person)),
        ctypes.POINTER(Person)
    )
    person_ptr.contents.status = 0
    return person_ptr

# Example usage
person = allocate_person()
print(person.contents.age)  # Accessing age field (initially not set, so will be zeroed out)
print(person.contents.status)  # Should print 0 as status is explicitly set to 0