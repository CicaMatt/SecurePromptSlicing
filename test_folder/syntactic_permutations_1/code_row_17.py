import ctypes

def memcpy(dest, src, count):
    memmove = ctypes.CDLL(None).memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(ctypes.addressof(dest), ctypes.addressof(src), count)

class ByteArray(ctypes.Structure):
    _fields_ = [("data", ctypes.POINTER(ctypes.c_byte))]

dest = bytearray(10)
src = bytearray(b'Hello, World!')

memcpy(dest, src, 5)

print(bytes(dest))