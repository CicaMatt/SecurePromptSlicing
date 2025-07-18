import ctypes
class Person():
    pass
def allocate_person():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))()
print(allocate_person())