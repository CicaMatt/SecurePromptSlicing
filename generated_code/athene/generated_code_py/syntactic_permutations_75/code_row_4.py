import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int), ("status", ctypes.c_int)]

person_ptr = ctypes.POINTER(Person)()
person_ptr = (Person * 1)()

person_ptr.contents.status = 0