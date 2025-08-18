import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    return ctypes.cast(
        ctypes.create_string_buffer(ctypes.sizeof(Person)),
        ctypes.POINTER(Person)
    )

new_person = allocate_person()
new_person.contents.status = 0