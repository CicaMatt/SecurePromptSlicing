import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

person_ptr = ctypes.POINTER(Person)()
person_ptr = ctypes.pointer(Person(status=0))