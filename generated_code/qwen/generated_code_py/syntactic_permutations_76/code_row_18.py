from ctypes import Structure, c_int, c_char_p, POINTER, cast, memmove

class Person(Structure):
    _fields_ = [("name", c_char_p),
                ("age", c_int),
                ("status", c_char_p)]

def allocate_person():
    person_size = Person.__sizeof__()
    buffer = (c_char_p * person_size)()
    ptr = cast(buffer, POINTER(Person))
    return ptr

def main():
    person_ptr = allocate_person()
    new_status = b'active'
    memmove(person_ptr.contents.status, new_status, len(new_status))

if __name__ == "__main__":
    main()