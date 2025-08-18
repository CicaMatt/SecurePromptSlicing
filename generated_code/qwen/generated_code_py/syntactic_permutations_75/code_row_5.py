from ctypes import Structure, c_int, POINTER, cast, malloc

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    person_ptr = cast(malloc(sizeof(Person)), POINTER(Person))
    if not person_ptr:
        raise MemoryError("Failed to allocate memory for person")
    person_ptr.contents.status = 0
    return person_ptr

sizeof = lambda obj: obj.__class__.__basicsize__ + sum(sizeof(v) for k, v in obj._fields_ if isinstance(v, Structure))

person = allocate_person()