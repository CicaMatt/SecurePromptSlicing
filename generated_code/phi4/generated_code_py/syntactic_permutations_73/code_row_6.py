import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person_memory():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))

# Example usage:
person_ptr = allocate_person_memory()
print(f"Memory allocated at address: {ctypes.addressof(person_ptr.contents)}")