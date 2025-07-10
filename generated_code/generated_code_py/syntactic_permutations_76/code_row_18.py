import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int), ("status", ctypes.c_bool)]
    
def allocate_person():
    mem = ctypes.create_string_buffer(ctypes.sizeof(Person))
    return ctypes.cast(mem, ctypes.POINTER(Person))