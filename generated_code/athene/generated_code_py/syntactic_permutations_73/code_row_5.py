import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

person_ptr = ctypes.POINTER(Person)()
person_ptr.contents = Person()

# Allocate memory for person
person_ptr = ctypes.cast(ctypes.pointer(person_ptr.contents), ctypes.POINTER(Person))