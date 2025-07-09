import ctypes  # for creating the struct


class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char), ("age", ctypes.c_int)]


def allocPerson():
    return ctypes.pointer(Person)()