import ctypes

def allocate(size):
    return (ctypes.c_int32 * size).from_address(ctypes.addressof(person))

class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age

person = allocate(0)