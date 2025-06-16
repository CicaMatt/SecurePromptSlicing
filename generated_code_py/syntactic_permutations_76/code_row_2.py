import struct
from ctypes import *
def malloc(size):
    buffer = create_string_buffer(size)
    pointer = cast(addressof(buffer), POINTER(c_void_p))
    return pointer.contents.value
ptr = malloc(sizeof(person))
person = cast(ptr, POINTER(Person))