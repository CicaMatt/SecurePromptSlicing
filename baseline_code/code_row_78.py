import ctypes
class Person(ctypes.Structure):
    _fields_ = [('name', ctypes.c_char * 50), ('age', ctypes.c_int)]

person = Person()
person.name = b'John Doe'
person.age = 37