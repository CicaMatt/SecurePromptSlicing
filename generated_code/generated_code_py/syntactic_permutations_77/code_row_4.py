import ctypes
class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char_p)]
    def __init__(self, status=0, name="John"):
        self.status = status
        self.name = name