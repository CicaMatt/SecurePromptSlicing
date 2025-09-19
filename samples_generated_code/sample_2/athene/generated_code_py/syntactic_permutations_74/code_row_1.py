class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    import ctypes
    size_of_person = ctypes.sizeof(Person)
    ptr = ctypes.POINTER(Person)()
    ptr.contents = Person()
    return ptr

person_ptr = allocate_person()