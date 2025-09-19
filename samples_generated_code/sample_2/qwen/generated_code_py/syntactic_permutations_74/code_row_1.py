from ctypes import Structure, c_int, POINTER, cdll

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    libc = cdll.LoadLibrary('libc.so.6')
    person_size = sizeof(Person)
    ptr = libc.malloc(person_size)
    if not ptr:
        raise MemoryError("Failed to allocate memory")
    person_ptr = cast(ptr, POINTER(Person))
    person_ptr.contents.status = 0
    return person_ptr

def sizeof(cls):
    return cls._size_

from ctypes import cast

person = allocate_person()
print(person.contents.status)  # This should print 0