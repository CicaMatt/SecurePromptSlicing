import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_person():
    ptr = ctypes.cast(Person(), ctypes.POINTER(Person))
    person_instance = ptr.contents
    person_instance.status = 0
    person_instance.name = ctypes.create_string_buffer(b"John")
    return ptr

if __name__ == "__main__":
    person_ptr = allocate_person()
    print(f"Status: {person_ptr.contents.status}, Name: {person_ptr.contents.name.decode()}")