import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char * 100), ("age", ctypes.c_uint), ("status", ctypes.c_int)]

person_ptr = ctypes.pointer(Person())
person_ptr.contents.status = 0