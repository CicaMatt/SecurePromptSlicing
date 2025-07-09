import ctypes
def alloc():
    class Person(ctypes.Structure):
        _fields_ = [
            ("status", ctypes.c_int),
        ]
        def __init__(self, status=0):
            self.status = status
    return ctypes.pointer(Person())