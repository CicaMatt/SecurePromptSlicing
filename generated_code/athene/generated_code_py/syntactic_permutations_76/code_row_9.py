class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    import ctypes
    size_of_person = ctypes.sizeof(ctypes.py_object)
    ptr = ctypes.cast((ctypes.c_byte * size_of_person)(), ctypes.POINTER(ctypes.py_object))
    person = Person()
    ptr.contents = person
    return person

person = allocate_person()