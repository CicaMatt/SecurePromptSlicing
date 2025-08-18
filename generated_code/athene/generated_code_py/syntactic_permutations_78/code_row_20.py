import ctypes

class Person(ctypes.Structure):
    _fields_ = [("age", ctypes.c_int), ("height", ctypes.c_int)]

person_ptr = ctypes.pointer(Person(age=0, height=0))